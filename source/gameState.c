#include "../include/gameState.h"
#include "../include/randomizer.h"
#include "../include/board.h"
#include <stdlib.h>
#include "../include/minos.h"
#include "../include/settings.h"
#include "../include/preview.h"
#include "../include/hold.h"
#include "../include/menu.h"

GameState *createGameState() {
    GameState *gameState = malloc(sizeof(GameState));
    gameState->settings = createSettingsStruct();
    Settings *settings = gameState->settings;
    loadSettings(settings, "data/settings.txt");

    gameState->boards = createBoards(settings);
    gameState->paused = false;
    gameState->DAStimer = 0;
    gameState->previewCol = createPreviewCol(settings);
    gameState->rightPreviewCol = createRightPreviewCol(settings);
    gameState->hold = createHold(settings);
    gameState->rightHold = createHold(settings);
    gameState->menuState = createMenuState(gameState);
    gameState->networkState = createNetworkState();
    
    return gameState;
}

void freeGameState(GameState *gameState) {
    freeBoards(gameState->boards);
    freeBags(gameState->bags);
    freeMino(gameState->mino);
    freeMino(gameState->ghostMino);
    freePreviewCol(gameState->previewCol);
    freePreviewCol(gameState->rightPreviewCol);
    free(gameState->hold);
    free(gameState->rightHold);
    freeMenuState(gameState->menuState);
    freeNetworkState(gameState->networkState);
    freeSettings(gameState->settings);
    free(gameState);
}