#include "../include/gameState.h"
#include "../include/hold.h"
#include <stdlib.h>
#include "../include/settings.h"
#include "../include/tetrisLogic.h"
#include "../include/preview.h"
#include <stdio.h>

static int MINO_SHAPES[7][4][2] = {
    [MinoI] = {{-1,0},{0,0},{1,0},{2,0}},
    [MinoO] = {{0,0},{1,0},{0,1},{1,1}},
    [MinoT] = {{-1,0},{0,0},{1,0},{0,-1}},
    [MinoL] = {{-1,0},{0,0},{1,0},{1,-1}},
    [MinoJ] = {{-1,-1},{-1,0},{0,0},{1,0}},
    [MinoS] = {{-1,0},{0,0},{0,-1},{1,-1}},
    [MinoZ] = {{-1,-1},{0,-1},{0,0},{1,0}}
};

static Color MINO_COLORS[7] = {
    [MinoI] = SKYBLUE, [MinoO] = YELLOW, [MinoT] = PURPLE,
    [MinoL] = ORANGE, [MinoJ] = DARKBLUE, [MinoS] = GREEN, [MinoZ] = RED
};

Hold *createHold(Settings *settings) {
    Hold *hold = malloc(sizeof(Hold));
    int blockSize = settings->BlockSize;
    float outline = settings->OutlineThickness;

    hold->rect.x = settings->StartX - 3*blockSize - 2*outline;
    hold->rect.y = settings->StartY - 2*outline;
    hold->rect.width = 3*blockSize;
    hold->rect.height = 3*blockSize;
    hold->hasMino = false;
    
    return hold;
}

void drawHold(GameState *gameState) {
    Settings *settings = gameState->settings;
    Hold *hold = gameState->hold;
    DrawRectangleLinesEx(hold->rect, settings->OutlineThickness, settings->BoardEdgeColor);

    int holdBlockSize = settings->BlockSize / 2;
    Color color = MINO_COLORS[hold->minoType];

    int centerX = hold->rect.x + hold->rect.width / 2;
    int centerY = hold->rect.y + hold->rect.height / 2;

    if(hold->hasMino) {
        for (int i = 0; i < 4; i++) {
        int ox = MINO_SHAPES[hold->minoType][i][0];
        int oy = MINO_SHAPES[hold->minoType][i][1];

        Rectangle cell = {
            centerX + ox * holdBlockSize - holdBlockSize / 2,
            centerY + oy * holdBlockSize - holdBlockSize / 2,
            holdBlockSize,
            holdBlockSize
        };
        DrawRectangleRec(cell, color);
        DrawRectangleLinesEx(cell, settings->OutlineThickness, settings->BoardEdgeColor);
        }
    }
}

void drawRightHold(GameState *gameState) {
    Settings *settings = gameState->settings;
    Hold *hold = gameState->rightHold;

    Rectangle rightHoldRect = hold->rect;
    rightHoldRect.x += 800;
    DrawRectangleLinesEx(rightHoldRect, settings->OutlineThickness, settings->BoardEdgeColor);

    int holdBlockSize = settings->BlockSize / 2;
    Color color = MINO_COLORS[hold->minoType];

    int centerX = rightHoldRect.x + rightHoldRect.width / 2;
    int centerY = rightHoldRect.y + rightHoldRect.height / 2;

    if(hold->hasMino) {
        for (int i = 0; i < 4; i++) {
        int ox = MINO_SHAPES[hold->minoType][i][0];
        int oy = MINO_SHAPES[hold->minoType][i][1];

        Rectangle cell = {
            centerX + ox * holdBlockSize - holdBlockSize / 2,
            centerY + oy * holdBlockSize - holdBlockSize / 2,
            holdBlockSize,
            holdBlockSize
        };
        DrawRectangleRec(cell, color);
        DrawRectangleLinesEx(cell, settings->OutlineThickness, settings->BoardEdgeColor);
        }
    }
}

void hold(GameState *gameState) {
    Hold *hold = gameState->hold;
    if(!hold->hasMino) {
        holdNoMino(gameState);
        return;
    }

    MinoType newMino = hold->minoType;
    hold->minoType = gameState->mino->minoType;
    freeMino(gameState->mino);
    switch(newMino) {
        case MinoI:
            gameState->mino = spawnI(gameState->boards->leftBoard);
            break;
        case MinoO:
            gameState->mino = spawnO(gameState->boards->leftBoard);
            break;
        case MinoT:
            gameState->mino = spawnT(gameState->boards->leftBoard);
            break;
        case MinoL:
            gameState->mino = spawnL(gameState->boards->leftBoard);
            break;
        case MinoJ:
            gameState->mino = spawnJ(gameState->boards->leftBoard);
            break;
        case MinoS:
            gameState->mino = spawnS(gameState->boards->leftBoard);
            break;
        case MinoZ:
            gameState->mino = spawnZ(gameState->boards->leftBoard);
            break;
        default:
            printf("\nbag gave a mino out of scope. ");
    }
    

    updatePreviewCol(gameState->previewCol, gameState->bags);
    spawnGhostMino(gameState);
}

void holdNoMino(GameState *gameState) {
    gameState->hold->minoType = gameState->mino->minoType;
    gameState->hold->hasMino = true;

    freeMino(gameState->mino);
    switch(getNextMino(gameState->bags->bag1)) {
        case I_MINO:
            gameState->mino = spawnI(gameState->boards->leftBoard);
            break;
        case O_MINO:
            gameState->mino = spawnO(gameState->boards->leftBoard);
            break;
        case T_MINO:
            gameState->mino = spawnT(gameState->boards->leftBoard);
            break;
        case L_MINO:
            gameState->mino = spawnL(gameState->boards->leftBoard);
            break;
        case J_MINO:
            gameState->mino = spawnJ(gameState->boards->leftBoard);
            break;
        case S_MINO:
            gameState->mino = spawnS(gameState->boards->leftBoard);
            break;
        case Z_MINO:
            gameState->mino = spawnZ(gameState->boards->leftBoard);
            break;
        default:
            printf("\nbag gave a mino out of scope. ");
    }
    updatePreviewCol(gameState->previewCol, gameState->bags);
    spawnGhostMino(gameState);
}