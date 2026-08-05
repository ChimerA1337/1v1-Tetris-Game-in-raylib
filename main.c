
#include "raylib.h"
#include "include/board.h"
#include "include/input.h"
#include "include/gameState.h"
#include "include/minos.h"
#include "include/settings.h"
//#include <stdio.h>
#include "include/block.h"
#include "include/preview.h"
#include "include/hold.h"
#include "include/menu.h"
#include "include/network.h"

int main(void) {
    // Initialization
    Settings *settings = createSettingsStruct();
    loadSettings(settings, "data/settings.txt");
    GameState *gameState = createGameState(settings);

    InitWindow(settings->ScreenWidth, settings->ScreenHeight, "silly");
    SetExitKey(KEY_NULL);
    SetTargetFPS(settings->FrameRate);

    // Main game loop
    while (!WindowShouldClose()) {
        if(gameState->menuState->running) {
            BeginDrawing();
            ClearBackground(BLACK);
            gameState->menuState->handle(gameState->menuState);
                if(gameState->menuState->whichMenu == gamingMenu) {
                    handleInput(gameState, settings);
                    drawBoards(gameState->boards, settings);
                    drawPreviewCol(gameState->previewCol, settings);
                    drawHold(gameState, settings);
                    drawMino(gameState->mino, settings);
                    drawMino(gameState->ghostMino, settings);
                }
                if(gameState->menuState->whichMenu == multiplayerMenu) {
                    recieveBoardState(gameState);
                    handleInput(gameState, settings);
                    drawBoards(gameState->boards, settings);
                    drawPreviewCol(gameState->previewCol, settings);
                    drawHold(gameState, settings);
                    drawMino(gameState->mino, settings);
                    drawMino(gameState->ghostMino, settings);
                }
            EndDrawing();
        }
        else {
            freeGameState(gameState);
            freeSettings(settings);
            CloseWindow();
            return 0;
        }
    }
    //de-initialization
    freeGameState(gameState);
    freeSettings(settings);
    CloseWindow();
    return 0;
}