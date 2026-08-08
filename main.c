
#include "raylib.h"
#include "include/board.h"
#include "include/input.h"
#include "include/gameState.h"
#include "include/minos.h"
#include "include/settings.h"
#include <stdio.h>
#include <enet/enet.h>
#include "include/block.h"
#include "include/preview.h"
#include "include/hold.h"
#include "include/menu.h"
#include "include/network.h"

int main(void) {
    // Initialization

    initializeENet();
    GameState *gameState = createGameState();
    Settings *settings = gameState->settings;

    InitWindow(settings->ScreenWidth, settings->ScreenHeight, "silly");
    SetExitKey(KEY_NULL);
    SetTargetFPS(settings->FrameRate);

    // Main game loop
    while (!WindowShouldClose()) {
        pollNetworkEvents(gameState);
        if(gameState->menuState->running) {
            BeginDrawing();
            ClearBackground(BLACK);
            gameState->menuState->handle(gameState->menuState);
                if(gameState->menuState->whichMenu == gamingMenu) {
                    handleInput(gameState);
                    drawBoards(gameState->boards, settings);
                    drawPreviewCol(gameState->previewCol, settings);
                    drawRightPreviewCol(gameState->rightPreviewCol, settings);
                    drawHold(gameState);
                    drawRightHold(gameState);
                    drawMino(gameState->mino, settings);
                    drawMino(gameState->ghostMino, settings);
                }
                if(gameState->menuState->whichMenu == multiplayerMenu) {
                    handleInput(gameState);
                    drawBoards(gameState->boards, settings);
                    drawPreviewCol(gameState->previewCol, settings);
                    drawRightPreviewCol(gameState->rightPreviewCol, settings);
                    drawHold(gameState);
                    drawRightHold(gameState);
                    drawMino(gameState->mino, settings);
                    drawMino(gameState->ghostMino, settings);
                }
            EndDrawing();
        }
        else {
            freeGameState(gameState);
            CloseWindow();
            return 0;
        }
    }
    //de-initialization
    freeGameState(gameState);
    CloseWindow();
    return 0;
}