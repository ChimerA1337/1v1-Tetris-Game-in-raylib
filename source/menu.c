#include "raylib.h"
#include "../include/menu.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../include/definitions.h"
#include "../include/settings.h"
#include <netdb.h>
#include <arpa/inet.h>
#include "../include/network.h"
#include "../include/gameState.h"
#include "../include/tetrisLogic.h"
#include "../include/preview.h"


MenuState *createMenuState(GameState *gameState) {
    MenuState *menuState = malloc(sizeof(MenuState));
    menuState->running = true;
    menuState->whichMenu = mainMenu;
    menuState->gameState = gameState;
    menuState->settings = gameState->settings;
    menuState->listeningForBind = false;
    menuState->promptHost = false;
    menuState->promptJoin = false;
    menuState->bindTarget = NULL;
    menuState->joinIpBuffer[0] = '\0';
    menuState->joinIpLength = 0;
    menuState->getUser = false;
    menuState->isHosting = false;

    menuState->mainMenu = createMainMenu();
    menuState->onlineMenu = createOnlineMenu();
    menuState->lobbyMenu = createLobbyMenu();
    menuState->settingsMenu = createSettingsMenu();
    menuState->gamingMenu = createGamingMenu();
    menuState->multiplayerMenu = createMultiplayerMenu();

    menuState->handle = handleMenus;
    return menuState;
}

MainMenu *createMainMenu() {
    MainMenu *menu = malloc(sizeof(MainMenu));

    menu->exit = createExitButton();
    menu->solo = createSoloButton();
    menu->online = createOnlineButton();
    menu->settings = createSettingsButton();

    menu->handle = handleMainMenu;
    return menu;
}

OnlineMenu *createOnlineMenu() {
    OnlineMenu *menu = malloc(sizeof(OnlineMenu));

    menu->exit = createExitButton();
    menu->host = createHostButton();
    menu->join = createJoinButton();
    
    menu->username[0] = '\0';
    menu->userLen = 0;

    menu->handle = handleOnlineMenu;
    return menu;
}

LobbyMenu *createLobbyMenu() {
    LobbyMenu *menu = malloc(sizeof(LobbyMenu));

    menu->exit = createExitButton();
    menu->start =createStartButton();

    menu->handle = handleLobbyMenu;
    return menu;
}

SettingsMenu *createSettingsMenu() {
    SettingsMenu *menu = malloc(sizeof(SettingsMenu));

    menu->exit = createExitButton();
    menu->save = createSaveButton();

    menu->editHardDrop = createEditHardDrop();
    menu->editSoftDrop = createEditSoftDrop();
    menu->editMoveLeft = createEditMoveLeft();
    menu->editMoveRight = createEditMoveRight();

    menu->handle = handleSettingsMenu;
    return menu;
}

GamingMenu *createGamingMenu() {
    GamingMenu *menu = malloc(sizeof(GamingMenu));

    menu->exit = createExitButton();

    menu->handle = handleGamingMenu;
    return menu;
}

MultiplayerMenu *createMultiplayerMenu() {
    MultiplayerMenu *menu = malloc(sizeof(MultiplayerMenu));

    menu->exit = createExitButton();

    menu->handle = handleMultiplayerMenu;
    return menu;
}

void freeMenuState(MenuState *menuState) {
    freeMainMenu(menuState->mainMenu);
    freeOnlineMenu(menuState->onlineMenu);
    freeSettingsMenu(menuState->settingsMenu);
    freeGamingMenu(menuState->gamingMenu);
    freeMultiplayerMenu(menuState->multiplayerMenu);
    free(menuState);
}

void freeMainMenu(MainMenu *menu) {
    free(menu->exit);
    free(menu->solo->button);
    free(menu->solo);
    free(menu->online->button);
    free(menu->online);
    free(menu->settings->button);
    free(menu->settings);
    free(menu);
}

void freeOnlineMenu(OnlineMenu *menu) {
    free(menu->exit);
    free(menu->host->button);
    free(menu->host);
    free(menu->join->button);
    free(menu->join);
    free(menu);
}

void freeLobbyMenu(LobbyMenu *menu) {
    free(menu->exit);
    free(menu->start);
    free(menu);
}

void freeSettingsMenu(SettingsMenu *menu) {
    free(menu->exit);
    free(menu->save->button);
    free(menu->save);

    free(menu->editHardDrop);
    free(menu->editSoftDrop);
    free(menu->editMoveLeft);
    free(menu->editMoveRight);

    free(menu);
    
}

void freeGamingMenu(GamingMenu *menu) {
    free(menu->exit);
    free(menu);
}

void freeMultiplayerMenu(MultiplayerMenu *menu) {
    free(menu->exit);
    free(menu);
}

void handleMenus(MenuState *menuState) {
    MainMenu *mMenu = menuState->mainMenu;
    OnlineMenu *oMenu = menuState->onlineMenu;
    LobbyMenu *lMenu = menuState->lobbyMenu;
    SettingsMenu *sMenu = menuState->settingsMenu;
    GamingMenu *gMenu = menuState->gamingMenu;
    MultiplayerMenu *muMenu = menuState->multiplayerMenu;

    switch(menuState->whichMenu) {
        case mainMenu:
            handleMainMenu(mMenu);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if(mMenu->exit->isMouseOnTop(mMenu->exit)) 
                    menuState->running = false;
                if(mMenu->solo->button->isMouseOnTop(mMenu->solo->button)) {
                    menuState->whichMenu = gamingMenu;
                    srand(time(NULL));
                    menuState->gameState->bags = createBags();
                    spawnMinoNoDelete(menuState->gameState);
                    spawnGhostMinoNoDelete(menuState->gameState);
                    updatePreviewCol(menuState->gameState->previewCol, menuState->gameState->bags);
                    updatePreviewCol(menuState->gameState->rightPreviewCol, menuState->gameState->bags);
                }
                    
                if(mMenu->online->button->isMouseOnTop(mMenu->online->button)) {
                    menuState->whichMenu = onlineMenu;
                    menuState->getUser = true;
                }
                if(mMenu->settings->button->isMouseOnTop(mMenu->settings->button)) 
                    menuState->whichMenu = settingsMenu;
            }
            break;
        case onlineMenu:
            handleOnlineMenu(oMenu);
            promptJoin(menuState);
            getUsername(menuState);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if(oMenu->exit->isMouseOnTop(oMenu->exit)) 
                    menuState->whichMenu = mainMenu;
                if(oMenu->host->button->isMouseOnTop(oMenu->host->button)) {
                    menuState->promptHost = true;
                    menuState->isHosting = true;
                    menuState->whichMenu = lobbyMenu;
                    createHost(menuState->gameState->networkState);
                }
                if(oMenu->join->button->isMouseOnTop(oMenu->join->button)) {
                    menuState->promptJoin = true;
                    menuState->isHosting = false;
                }
            }
            break;
        case lobbyMenu:
            handleLobbyMenu(menuState);
            drawLobby(menuState);
            promptHost(menuState);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if(lMenu->exit->isMouseOnTop(lMenu->exit)) 
                    menuState->whichMenu = onlineMenu;
            }
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if(lMenu->start->isMouseOnTop(lMenu->start) && menuState->isHosting)
                    sendStart(menuState->gameState);
            }
            break;
        case settingsMenu:
            handleSettingsMenu(sMenu);
            promptBindingListen(menuState);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if(sMenu->exit->isMouseOnTop(sMenu->exit)) 
                    menuState->whichMenu = mainMenu;
                if(sMenu->editHardDrop->isMouseOnTop(sMenu->editHardDrop)) {
                    menuState->listeningForBind = true;
                    menuState->bindTarget = &menuState->settings->HardDrop;
                }
                if(sMenu->editHardDrop->isMouseOnTop(sMenu->editSoftDrop)) {
                    menuState->listeningForBind = true;
                    menuState->bindTarget = &menuState->settings->SoftDrop;
                }
                if(sMenu->editHardDrop->isMouseOnTop(sMenu->editMoveLeft)) {
                    menuState->listeningForBind = true;
                    menuState->bindTarget = &menuState->settings->MoveLeft;
                }
                if(sMenu->editHardDrop->isMouseOnTop(sMenu->editMoveRight)) {
                    menuState->listeningForBind = true;
                    menuState->bindTarget = &menuState->settings->MoveRight;
                }
                if(sMenu->save->button->isMouseOnTop(sMenu->save->button)) {
                    saveSettings(menuState->settings, "data/settings.txt");
                    loadSettings(menuState->settings, "data/settings.txt");
                }
            }
            break;
        case gamingMenu:
            handleGamingMenu(gMenu);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if(gMenu->exit->isMouseOnTop(gMenu->exit)) 
                    menuState->whichMenu = mainMenu;
            }
            break;
        case multiplayerMenu:
            handleMultiplayerMenu(muMenu);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if(muMenu->exit->isMouseOnTop(muMenu->exit))
                    menuState->whichMenu = lobbyMenu;
            }
            break;
    }
}

void handleMainMenu(MainMenu *menu) {
    menu->exit->draw(menu->exit);
    menu->exit->highlight(menu->exit);

    menu->solo->button->draw(menu->solo->button);
    menu->solo->button->highlight(menu->solo->button);
    menu->solo->extend(menu->solo);

    menu->online->button->draw(menu->online->button);
    menu->online->button->highlight(menu->online->button);
    menu->online->extend(menu->online);

    menu->settings->button->draw(menu->settings->button);
    menu->settings->button->highlight(menu->settings->button);
    menu->settings->extend(menu->settings);
}

void handleOnlineMenu(OnlineMenu *menu) {
    menu->exit->draw(menu->exit);
    menu->exit->highlight(menu->exit);

    menu->host->button->draw(menu->host->button);
    menu->host->button->highlight(menu->host->button);
    menu->host->extend(menu->host);

    menu->join->button->draw(menu->join->button);
    menu->join->button->highlight(menu->join->button);
    menu->join->extend(menu->join);
}

void handleLobbyMenu(MenuState *menu) {
    NetworkState *network = menu->gameState->networkState;

    menu->lobbyMenu->exit->draw(menu->lobbyMenu->exit);
    menu->lobbyMenu->exit->highlight(menu->lobbyMenu->exit);

    if(menu->isHosting) {
        menu->lobbyMenu->start->draw(menu->lobbyMenu->start);
        menu->lobbyMenu->start->highlight(menu->lobbyMenu->start);
    }
}

void handleSettingsMenu(SettingsMenu *menu) {
    DrawText("Controls", 100, 200, 40, DARKGRAY);

    menu->exit->draw(menu->exit);
    menu->exit->highlight(menu->exit);

    menu->save->button->draw(menu->save->button);
    menu->save->button->highlight(menu->save->button);
    menu->save->extend(menu->save);

    menu->editHardDrop->draw(menu->editHardDrop);
    menu->editHardDrop->highlight(menu->editHardDrop);

    menu->editSoftDrop->draw(menu->editSoftDrop);
    menu->editSoftDrop->highlight(menu->editSoftDrop);

    menu->editMoveLeft->draw(menu->editMoveLeft);
    menu->editMoveLeft->highlight(menu->editMoveLeft);

    menu->editMoveRight->draw(menu->editMoveRight);
    menu->editMoveRight->highlight(menu->editMoveRight);
}

void handleGamingMenu(GamingMenu *menu) {
    menu->exit->draw(menu->exit);
    menu->exit->highlight(menu->exit);
}

void handleMultiplayerMenu(MultiplayerMenu *menu) {
    menu->exit->draw(menu->exit);
    menu->exit->highlight(menu->exit);
}

MenuButton *createExitButton() {
    MenuButton *button = malloc(sizeof(MenuButton));
    button->color = MAROON_TRANSPARENT;
    button->rect.x = 0;
    button->rect.y = 50;
    button->rect.width = 150;
    button->rect.height = 50;
    button->textPos = (Vector2) {0+20, 45 + 20};
    button->font = GetFontDefault(); // Use a custom font later, smth like roboto or smth
    button->fontSize = 20;
    button->textColor = RED;
    button->text = "Back";
    button->spacing = 5;

    button->draw = drawButton;
    button->isMouseOnTop = isMouseOnTop;
    button->highlight = highlightButton;

    return button;
}

MenuButtonExtend *createSoloButton() {
    MenuButtonExtend *menuButtonExtend = malloc(sizeof(MenuButtonExtend));
    MenuButton *button = malloc(sizeof(MenuButton));

    button->color = DARKPURPLE_TRANSPARENT;
    button->rect.x = 600;
    button->rect.y = 200;
    button->rect.width = 1300;
    button->rect.height = 100;
    button->textPos = (Vector2) {600 + 20, 200 + 20};
    button->font = GetFontDefault(); // Use a custom font later, smth like roboto or smth
    button->fontSize = 50;
    button->textColor = PURPLE;
    button->text = "Play Solo";
    button->spacing = 5;

    button->draw = drawButton;
    button->isMouseOnTop = isMouseOnTop;
    button->highlight = highlightButton;
    
    menuButtonExtend->button = button;
    
    menuButtonExtend->extend = extendButton;

    return menuButtonExtend;
}

MenuButtonExtend *createOnlineButton() {
    MenuButtonExtend *menuButtonExtend = malloc(sizeof(MenuButtonExtend));
    MenuButton *button = malloc(sizeof(MenuButton));

    button->color = ORANGE_TRANSPARENT;
    button->rect.x = 600;
    button->rect.y = 350;
    button->rect.width = 1300;
    button->rect.height = 100;
    button->textPos = (Vector2) {600 + 20, 350 + 20};
    button->font = GetFontDefault(); // Use a custom font later, smth like roboto or smth
    button->fontSize = 50;
    button->textColor = YELLOW;
    button->text = "Play Online";
    button->spacing = 5;

    button->draw = drawButton;
    button->isMouseOnTop = isMouseOnTop;
    button->highlight = highlightButton;
    
    menuButtonExtend->button = button;
    
    menuButtonExtend->extend = extendButton;

    return menuButtonExtend;
}

MenuButtonExtend *createSettingsButton() {
    MenuButtonExtend *menuButtonExtend = malloc(sizeof(MenuButtonExtend));
    MenuButton *button = malloc(sizeof(MenuButton));

    button->color = DARKGRAY_TRANSPARENT;
    button->rect.x = 600;
    button->rect.y = 500;
    button->rect.width = 1300;
    button->rect.height = 100;
    button->textPos = (Vector2) {600 + 20, 500 + 20};
    button->font = GetFontDefault(); // Use a custom font later, smth like roboto or smth
    button->fontSize = 50;
    button->textColor = LIGHTGRAY;
    button->text = "Settings";
    button->spacing = 5;

    button->draw = drawButton;
    button->isMouseOnTop = isMouseOnTop;
    button->highlight = highlightButton;
    
    menuButtonExtend->button = button;
    
    menuButtonExtend->extend = extendButton;

    return menuButtonExtend;
}

MenuButtonExtend *createSaveButton() {
    MenuButtonExtend *menuButtonExtend = malloc(sizeof(MenuButtonExtend));
    MenuButton *button = malloc(sizeof(MenuButton));

    button->color = BLUE_TRANSPARENT;
    button->rect.x = 600;
    button->rect.y = 700;
    button->rect.width = 1300;
    button->rect.height = 100;
    button->textPos = (Vector2) {600 + 20, 700 + 20};
    button->font = GetFontDefault(); // Use a custom font later, smth like roboto or smth
    button->fontSize = 50;
    button->textColor = SKYBLUE;
    button->text = "Save";
    button->spacing = 5;

    button->draw = drawButton;
    button->isMouseOnTop = isMouseOnTop;
    button->highlight = highlightButton;
    
    menuButtonExtend->button = button;
    
    menuButtonExtend->extend = extendButton;

    return menuButtonExtend;
}

MenuButton *createEditHardDrop() {
    MenuButton *button = malloc(sizeof(MenuButton));
    
    button->color = DARKPURPLE_TRANSPARENT;
    button->rect.x = 100;
    button->rect.y = 300;
    button->rect.width = 300;
    button->rect.height = 50;
    button->textPos = (Vector2) {100 + 20, 300 + 15};
    button->font = GetFontDefault(); // Use a custom font later, smth like roboto or smth
    button->fontSize = 20;
    button->textColor = PURPLE;
    button->text = "Rebind Hard Drop";
    button->spacing = 5;

    button->draw = drawButton;
    button->isMouseOnTop = isMouseOnTop;
    button->highlight = highlightButton;

    return button;
}

MenuButton *createEditSoftDrop() {
    MenuButton *button = malloc(sizeof(MenuButton));
    
    button->color = DARKPURPLE_TRANSPARENT;
    button->rect.x = 100;
    button->rect.y = 375;
    button->rect.width = 300;
    button->rect.height = 50;
    button->textPos = (Vector2) {100 + 20, 375 + 15};
    button->font = GetFontDefault(); // Use a custom font later, smth like roboto or smth
    button->fontSize = 20;
    button->textColor = PURPLE;
    button->text = "Rebind Soft Drop";
    button->spacing = 5;

    button->draw = drawButton;
    button->isMouseOnTop = isMouseOnTop;
    button->highlight = highlightButton;

    return button;
}

MenuButton *createEditMoveLeft() {
    MenuButton *button = malloc(sizeof(MenuButton));
    
    button->color = DARKPURPLE_TRANSPARENT;
    button->rect.x = 100;
    button->rect.y = 450;
    button->rect.width = 300;
    button->rect.height = 50;
    button->textPos = (Vector2) {100 + 20, 450 + 15};
    button->font = GetFontDefault(); // Use a custom font later, smth like roboto or smth
    button->fontSize = 20;
    button->textColor = PURPLE;
    button->text = "Rebind Move Left";
    button->spacing = 5;

    button->draw = drawButton;
    button->isMouseOnTop = isMouseOnTop;
    button->highlight = highlightButton;

    return button;
}

MenuButton *createEditMoveRight() {
    MenuButton *button = malloc(sizeof(MenuButton));
    
    button->color = DARKPURPLE_TRANSPARENT;
    button->rect.x = 100;
    button->rect.y = 525;
    button->rect.width = 300;
    button->rect.height = 50;
    button->textPos = (Vector2) {100 + 20, 525 + 15};
    button->font = GetFontDefault(); // Use a custom font later, smth like roboto or smth
    button->fontSize = 20;
    button->textColor = PURPLE;
    button->text = "Rebind Move Right";
    button->spacing = 5;

    button->draw = drawButton;
    button->isMouseOnTop = isMouseOnTop;
    button->highlight = highlightButton;

    return button;
}

MenuButtonExtend *createHostButton() {
    MenuButtonExtend *menuButtonExtend = malloc(sizeof(MenuButtonExtend));
    MenuButton *button = malloc(sizeof(MenuButton));

    button->color = DARKPURPLE_TRANSPARENT;
    button->rect.x = 600;
    button->rect.y = 350;
    button->rect.width = 1300;
    button->rect.height = 100;
    button->textPos = (Vector2) {600 + 20, 350 + 20};
    button->font = GetFontDefault(); // Use a custom font later, smth like roboto or smth
    button->fontSize = 50;
    button->textColor = PURPLE;
    button->text = "Host";
    button->spacing = 5;

    button->draw = drawButton;
    button->isMouseOnTop = isMouseOnTop;
    button->highlight = highlightButton;
    
    menuButtonExtend->button = button;
    
    menuButtonExtend->extend = extendButton;

    return menuButtonExtend;
}

MenuButtonExtend *createJoinButton() {
    MenuButtonExtend *menuButtonExtend = malloc(sizeof(MenuButtonExtend));
    MenuButton *button = malloc(sizeof(MenuButton));

    button->color = ORANGE_TRANSPARENT;
    button->rect.x = 600;
    button->rect.y = 500;
    button->rect.width = 1300;
    button->rect.height = 100;
    button->textPos = (Vector2) {600 + 20, 500 + 20};
    button->font = GetFontDefault(); // Use a custom font later, smth like roboto or smth
    button->fontSize = 50;
    button->textColor = YELLOW;
    button->text = "Join";
    button->spacing = 5;

    button->draw = drawButton;
    button->isMouseOnTop = isMouseOnTop;
    button->highlight = highlightButton;
    
    menuButtonExtend->button = button;
    
    menuButtonExtend->extend = extendButton;

    return menuButtonExtend;
}

MenuButton *createStartButton() {
    MenuButton *button = malloc(sizeof(MenuButton));
    button->color = MAROON_TRANSPARENT;
    button->rect.x = (float) 1600/2 + 100;
    button->rect.y = (float) 900/2 + 150;
    button->rect.width = (float) 1600/2 - 200;
    button->rect.height = (float) 900/2 - 200;
    button->textPos = (Vector2) {(float) 1600/2 + 100 +20, (float) 900/2 + 150 + 20};
    button->font = GetFontDefault(); // Use a custom font later, smth like roboto or smth
    button->fontSize = 40;
    button->textColor = RED;
    button->text = "Start";
    button->spacing = 5;

    button->draw = drawButton;
    button->isMouseOnTop = isMouseOnTop;
    button->highlight = highlightButton;

    return button;
}

void drawButton(MenuButton *button) {
    DrawRectangleRec(button->rect, button->color);
    DrawRectangleLinesEx(button->rect, 1.5, button->textColor);
    DrawTextEx(
        button->font,
        button->text,
        button->textPos,
        button->fontSize,
        button->spacing,
        button->textColor
    );
}

bool isMouseOnTop(MenuButton *button) {
    if(
        GetMouseX() > button->rect.x &&
        GetMouseX() < button->rect.x + button->rect.width &&
        GetMouseY() > button->rect.y &&
        GetMouseY() < button->rect.y + button->rect.height
    ) return true;
    return false;
}

void highlightButton(MenuButton *button) {
    if(button->isMouseOnTop(button)) DrawRectangleRec(button->rect, TRANSPARENT_WHITE);
}

void extendButton(MenuButtonExtend *extendButton) {
    float speed = 20;
    float minX = 400;
    float maxX = 600;

    if(
        extendButton->button->isMouseOnTop(extendButton->button) &&
        extendButton->button->rect.x >= minX
    ) {
        extendButton->button->rect.x -= speed;
        extendButton->button->textPos.x -= speed;
        if(extendButton->button->rect.x < minX) {
            extendButton->button->rect.x = minX;
            extendButton->button->textPos.x = minX+20;
        }
    }
    else if(extendButton->button->rect.x <= 600) {
        extendButton->button->rect.x += speed;
        extendButton->button->textPos.x += speed;
        if(extendButton->button->rect.x > maxX) {
            extendButton->button->rect.x = maxX;
            extendButton->button->textPos.x = maxX+20;
        }
    }
}

void promptBindingListen(MenuState *menuState) {
    if(!menuState->listeningForBind) return;

    Rectangle rec = {(float)1600/2 - 150, (float)900/2 - 150, 300, 200};
    DrawRectangleRec(rec, BLUE_TRANSPARENT);
    DrawRectangleLinesEx(rec, 1.5, SKYBLUE);
    DrawText("Enter a key...", 1600/2 - 150 + 20, 900/2 - 150 + 10, 40, SKYBLUE);

    int key = GetKeyPressed();
    if(key == KEY_ESCAPE) menuState->listeningForBind = false;
    if(key != 0) {
        *menuState->bindTarget = key;
        menuState->listeningForBind = false;
    }
}

void promptHost(MenuState *menuState) {
    if(!menuState->promptHost) return;
    menuState->gameState->networkState->hostUsername = menuState->onlineMenu->username;

    Rectangle rec = {(float)1600/2 - 300, (float)900/2 - 150, 600, 200};
    DrawRectangleRec(rec, DARKPURPLE_TRANSPARENT);
    DrawRectangleLinesEx(rec, 1.5, PURPLE);

    char hostname[128];
    char hostnameString[256] = "Hosting at: ";
    
    gethostname(hostname, sizeof(hostname));
    strcat(hostnameString, hostname);

    struct hostent *hostEntry = gethostbyname(hostname);
    char *IpBuffer = inet_ntoa(*((struct in_addr*) hostEntry->h_addr_list[0]));

    DrawText(hostnameString, 1600/2 - 300 + 20, 900/2 - 150 + 10, 40, PURPLE);
    DrawText(IpBuffer, 1600/2 - 300 + 20, 900/2 - 100 + 10, 40, PURPLE);

    int key = GetKeyPressed();
    if(key == KEY_ESCAPE) menuState->promptHost = false;
}

void promptJoin(MenuState *menuState) {
    if(!menuState->promptJoin) return;

    Rectangle rec = {(float)1600/2 - 300, (float)900/2 - 150, 600, 200};

    DrawRectangleRec(rec, ORANGE_TRANSPARENT);
    DrawRectangleLinesEx(rec, 1.5, YELLOW);

    DrawText("Enter Host IP: ", 1600/2 - 300 + 20, 900/2 - 150 + 10, 40, YELLOW);
    DrawText(menuState->joinIpBuffer, 1600/2 - 300 + 20, 900/2 - 150 + 60, 40, YELLOW);

    int ch = GetCharPressed();
    while (ch > 0) {
        // Only allow digits and '.' — valid IPv4 characters
        if ((ch >= '0' && ch <= '9') || ch == '.') {
            if (menuState->joinIpLength < 15) { // leave room for null terminator
                menuState->joinIpBuffer[menuState->joinIpLength] = (char)ch;
                menuState->joinIpLength++;
                menuState->joinIpBuffer[menuState->joinIpLength] = '\0';
            }
        }
        ch = GetCharPressed(); // check for more characters typed this frame
    }

    // Backspace support
    if (IsKeyPressed(KEY_BACKSPACE) && menuState->joinIpLength > 0) {
        menuState->joinIpLength--;
        menuState->joinIpBuffer[menuState->joinIpLength] = '\0';
    }

    // Submit on Enter
    if (IsKeyPressed(KEY_ENTER) && menuState->joinIpLength > 0) {
        NetworkState *network = menuState->gameState->networkState;
        createClient(network, menuState->joinIpBuffer);
        menuState->promptJoin = false;
        menuState->whichMenu = lobbyMenu;
        
        network->clientUsername = menuState->onlineMenu->username;
        //send(network->socket, network->clientUsername, strlen(network->clientUsername), 0);
    }

    if(IsKeyPressed(KEY_ESCAPE)) menuState->promptJoin = false;
}

void drawLobby(MenuState *menu) {
    Rectangle recHost = {100, 150, (float) 1600/2 - 200, (float) 900/2 - 200};
    Rectangle recClient = {(float) 1600/2 + 100, 150, (float) 1600/2 - 200, (float) 900/2 - 200};
    Rectangle recChat = {100, (float) 900/2 + 150, (float) 1600/2 - 100, (float) 900/2 - 200};

    DrawRectangleRec(recHost, BLUE_TRANSPARENT);
    DrawRectangleLinesEx(recHost, 1.5, SKYBLUE);
    DrawRectangleRec(recClient, ORANGE_TRANSPARENT);
    DrawRectangleLinesEx(recClient, 1.5, YELLOW);
    DrawRectangleRec(recChat, DARKGRAY_TRANSPARENT);
    DrawRectangleLinesEx(recChat, 1.5, GRAY);

    DrawText("testr", 100+20, 150+10, 30, SKYBLUE);
    DrawText("tost", (float) 1600/2 + 100+20, 150+10, 30, YELLOW);
}

void getUsername(MenuState *menu) {
    if(!menu->getUser) return;
    char *username = menu->onlineMenu->username;
    int *length = &menu->onlineMenu->userLen;

    Rectangle rec = {(float)1600/2 - 300, (float)900/2 - 150, 600, 200};

    DrawRectangleRec(rec, ORANGE_TRANSPARENT);
    DrawRectangleLinesEx(rec, 1.5, YELLOW);

    DrawText("Enter username: ", 1600/2 - 300 + 20, 900/2 - 150 + 10, 40, YELLOW);
    DrawText(menu->onlineMenu->username, 1600/2 - 300 + 20, 900/2 - 150 + 60, 40, YELLOW);

    int ch = GetCharPressed();
    while (ch > 0) {
        if (*length < 15) { // leave room for null terminator
            username[*length] = (char)ch;
            (*length)++;
            username[*length] = '\0';
        }
        ch = GetCharPressed(); // check for more characters typed this frame
    }

    // Backspace support
    if (IsKeyPressed(KEY_BACKSPACE) && length > 0) {
        length--;
        username[*length] = '\0';
    }

    // Submit on Enter
    if (IsKeyPressed(KEY_ENTER) && length > 0) {
        menu->getUser = false;
    }

    if (IsKeyPressed(KEY_ESCAPE)) menu->getUser = false;
}