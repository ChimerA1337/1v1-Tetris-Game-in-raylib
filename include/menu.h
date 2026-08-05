#ifndef MENU_H
#define MENU_H

#include "board.h"
#include "network.h"

typedef struct GameState GameState;
typedef struct MultiplayerMenu MultiplayerMenu;
typedef struct MenuState MenuState;

typedef enum WhichMenu {
    mainMenu,
    onlineMenu,
    lobbyMenu,
    settingsMenu,
    gamingMenu,
    multiplayerMenu
} WhichMenu;

typedef struct MenuButton {
    Rectangle rect;
    Color color;

    Vector2 textPos;
    const char *text;
    Font font;
    float fontSize;
    Color textColor;
    float spacing;

    bool (*isMouseOnTop) (struct MenuButton *self);
    void (*draw) (struct MenuButton *self);
    void (*highlight) (struct MenuButton *self);
} MenuButton;

typedef struct MenuButtonExtend {
    MenuButton *button;

    void (*extend) (struct MenuButtonExtend *self);
} MenuButtonExtend;

typedef struct MainMenu {
    MenuButton *exit;
    MenuButtonExtend *solo;
    MenuButtonExtend *online;
    MenuButtonExtend *settings;

    void (*handle) (struct MainMenu *self);
} MainMenu;

typedef struct OnlineMenu {
    MenuButton *exit;
    MenuButtonExtend *host;
    MenuButtonExtend *join;

    char username[25];
    int userLen;

    void (*handle) (struct OnlineMenu *self);
} OnlineMenu;

typedef struct LobbyMenu {
    MenuButton *exit;
    
    MenuButton *start;

    void (*handle) (struct MenuState *self);
} LobbyMenu;

typedef struct SettingsMenu {
    MenuButton *exit;
    MenuButtonExtend *save;

    MenuButton *editHardDrop;
    MenuButton *editSoftDrop;
    MenuButton *editMoveLeft;
    MenuButton *editMoveRight;

    void (*handle) (struct SettingsMenu *self);
} SettingsMenu;

typedef struct GamingMenu {
    MenuButton *exit;

    void (*handle) (struct GamingMenu *self);
} GamingMenu;

struct MultiplayerMenu {
    MenuButton *exit;

    void (*handle) (struct MultiplayerMenu *self);
};

typedef struct MenuState {
    WhichMenu whichMenu;
    bool running;
    GameState *gameState;
    Settings *settings;
    bool listeningForBind;
    bool promptHost;
    bool promptJoin;
    bool getUser;
    bool isHosting;
    int *bindTarget;

    char joinIpBuffer[16];
    int joinIpLength;

    MainMenu *mainMenu;
    OnlineMenu *onlineMenu;
    LobbyMenu *lobbyMenu;
    SettingsMenu *settingsMenu;
    GamingMenu *gamingMenu;
    MultiplayerMenu *multiplayerMenu;
    
    void (*handle) (struct MenuState *self);
} MenuState;

MenuState *createMenuState(GameState *gameState, Settings *settings);
    MenuButton *createExitButton();
    MainMenu *createMainMenu();
        MenuButtonExtend *createSoloButton();
        MenuButtonExtend *createOnlineButton();
        MenuButtonExtend *createSettingsButton();
    OnlineMenu *createOnlineMenu();
        MenuButtonExtend *createHostButton();
        MenuButtonExtend *createJoinButton();
        void getUsername(MenuState *menu);
    LobbyMenu *createLobbyMenu();
        void drawLobby(MenuState *menu);
        MenuButton *createStartButton();
    SettingsMenu *createSettingsMenu();
        MenuButtonExtend *createSaveButton();
        MenuButton *createEditHardDrop();
        MenuButton *createEditSoftDrop();
        MenuButton *createEditMoveLeft();
        MenuButton *createEditMoveRight();
    GamingMenu *createGamingMenu();
    MultiplayerMenu *createMultiplayerMenu();

void freeMenuState(MenuState *menuState);
    void freeMainMenu(MainMenu *menu);
    void freeOnlineMenu(OnlineMenu *menu);
    void freeLobbyMenu(LobbyMenu *menu);
    void freeSettingsMenu(SettingsMenu *menu);
    void freeGamingMenu(GamingMenu *menu);
    void freeMultiplayerMenu(MultiplayerMenu *menu);

void handleMenus(MenuState *menuState);
    void handleMainMenu(MainMenu *menu);
    void handleOnlineMenu(OnlineMenu *menu);
    void handleLobbyMenu(MenuState *menu);
    void handleSettingsMenu(SettingsMenu *menu);
    void handleGamingMenu(GamingMenu *menu);
    void handleMultiplayerMenu(MultiplayerMenu *menu);

bool isMouseOnTop(MenuButton *button);
void drawButton(MenuButton *button);
void highlightButton(MenuButton *button);
void extendButton(MenuButtonExtend *extendButton);

void promptBindingListen(MenuState *menuState);
void promptHost(MenuState *menuState);
void promptJoin(MenuState *menuState);
void updateHosting(MenuState *menuState);

#endif