#include "../include/gameState.h"
#include "../include/randomizer.h"
#include "../include/board.h"
#include <stdlib.h>
#include <time.h>
#include "../include/minos.h"
#include "../include/tetrisLogic.h"
#include "../include/settings.h"
#include "../include/preview.h"
#include "../include/hold.h"
#include "../include/menu.h"

GameState *createGameState(Settings *settings) {
    //srand(time(NULL));
    Bags *bags = createBags();
    Boards *boards = createBoards(settings);

    GameState *gameState = malloc(sizeof(GameState));
    gameState->bags = bags;
    gameState->boards = boards;
    spawnMinoNoDelete(gameState, settings);
    spawnGhostMinoNoDelete(gameState, settings);
    gameState->paused = false;
    gameState->DAStimer = 0;
    gameState->previewCol = createPreviewCol(settings);
    updatePreviewCol(gameState->previewCol, gameState->bags);
    gameState->hold = createHold(settings);
    gameState->menuState = createMenuState(gameState, settings);
    gameState->networkState = createNetworkState();

    return gameState;
}

void freeGameState(GameState *gameState) {
    freeBoards(gameState->boards);
    freeBags(gameState->bags);
    freeMino(gameState->mino);
    freeMino(gameState->ghostMino);
    freePreviewCol(gameState->previewCol);
    free(gameState->hold);
    freeMenuState(gameState->menuState);
    freeNetworkState(gameState->networkState);

    free(gameState);
    gameState = NULL;
}