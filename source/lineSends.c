#include "raylib.h"
#include "../include/lineSends.h"
#include "../include/gameState.h"
#include "../include/settings.h"
#include "../include/block.h"
#include <stdlib.h>
#include <stdio.h>


void recieveLines(GameState *gameState) {
    int ignoredColumn = rand() % (gameState->settings->GridWidth);
    for(int i = 0; i < gameState->linesToRecieve; i++) {
        recieveLine(gameState, ignoredColumn);
    }
    if(gameState->linesToRecieve > 0) {
        printf("The ignored col: %d\n", ignoredColumn);
        gameState->linesToRecieve = 0;
    }
}

void recieveLine(GameState *gameState, int ignoredColumn) {
    Board *board = gameState->boards->leftBoard;
    Settings *settings = gameState->settings;
    for(int j = 0; j < settings->GridWidth; j++) {
        for(int i = 0; i < settings->GridHeight-1; i++) {
            replaceBlockUp(board, j, i);
        }

        if(j == ignoredColumn) {
            getBlock(board, j, settings->GridHeight-1)->color = settings->BoardColor;
            getBlock(board, j, settings->GridHeight-1)->occupied = false;
        }
        else {
            getBlock(board, j, settings->GridHeight-1)->color = settings->GarbageColor;
            getBlock(board, j, settings->GridHeight-1)->occupied = true;
        }
    }
}

int lineSendCalculation(GameState *gameState) {

}