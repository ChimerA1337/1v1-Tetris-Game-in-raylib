#include "../include/gameState.h"
#include <stdio.h>
#include "../include/tetrisLogic.h"
#include "../include/block.h"
#include "../include/minos.h"
#include "../include/settings.h"
#include "../include/preview.h"
#include "../include/definitions.h"
#include "../include/lineSends.h"

void spawnMinoNoDelete(GameState *gameState) {
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
}

void spawnMino(GameState *gameState) {
    hardDrop(gameState);
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
        case REFRESH_BAG:
            refreshBags(gameState->bags);
            spawnMinoNoDelete(gameState);
            break;
        default:
            printf("\nbag gave a mino out of scope. ");
    }
    updatePreviewCol(gameState->previewCol, gameState->bags);
    spawnGhostMino(gameState);
}

void spawnGhostMinoNoDelete(GameState *gameState) {
    Mino *ghostMino = copyMino(gameState->mino);

    ghostMino->color = ColorAlpha(ghostMino->color, gameState->settings->GhostMinoAlpha);

    gameState->ghostMino = ghostMino;
    softDropGhost(gameState);
}

void spawnGhostMino(GameState *gameState) {
    Mino *ghostMino = copyMino(gameState->mino);
    clearMino(gameState->ghostMino, gameState->settings->BoardColor);
    freeMino(gameState->ghostMino);

    ghostMino->color = ColorAlpha(ghostMino->color,gameState->settings->GhostMinoAlpha);

    gameState->ghostMino = ghostMino;
    softDropGhost(gameState);
}

void hardDrop(GameState *gameState) {
    softDrop(gameState);
    commitMinoToBoard(gameState);
    clearLines(gameState);
}

void softDrop(GameState *gameState) {
    dropMino(gameState);
    correctMinoPos(gameState);
}

void dropMino(GameState *gameState) {
    if(!isDownLegal(gameState)) {
        moveMinoY(gameState->mino, -1);
        return;
    }
    moveMinoY(gameState->mino, 1);
    dropMino(gameState);
}

void softDropGhost(GameState *gameState) {
    dropMinoGhost(gameState);
    correctMinoPosGhost(gameState);
}

void dropMinoGhost(GameState *gameState) {
    if(!isDownLegalGhost(gameState)) {
        moveMinoY(gameState->ghostMino, -1);
        return;
    }
    moveMinoY(gameState->ghostMino, 1);
    dropMinoGhost(gameState);
}

void commitMinoToBoard(GameState *gameState) {
    Board *board = gameState->boards->leftBoard;
    Mino *mino = gameState->mino;

    getBlock(board, mino->anchor->x, mino->anchor->y)->color = mino->color;
    getBlock(board, mino->block1->x, mino->block1->y)->color = mino->color;
    getBlock(board, mino->block2->x, mino->block2->y)->color = mino->color;
    getBlock(board, mino->block3->x, mino->block3->y)->color = mino->color;

    getBlock(board, mino->anchor->x, mino->anchor->y)->occupied = true;
    getBlock(board, mino->block1->x, mino->block1->y)->occupied = true;
    getBlock(board, mino->block2->x, mino->block2->y)->occupied = true;
    getBlock(board, mino->block3->x, mino->block3->y)->occupied = true;
}

void moveMinoY(Mino *mino, int y) {
    mino->anchor->y+=y;
    mino->block1->y+=y;
    mino->block2->y+=y;
    mino->block3->y+=y;
}

void moveMinoX(Mino *mino, int x) {
    mino->anchor->x+=x;
    mino->block1->x+=x;
    mino->block2->x+=x;
    mino->block3->x+=x;
}

void moveLeft(GameState *gameState) {
    moveMinoX(gameState->mino, -1);
    if(!isLeftLegal(gameState))
        moveMinoX(gameState->mino, 1);
    correctMinoPos(gameState);

    copyMinoPosition(gameState->mino, gameState->ghostMino);
    softDropGhost(gameState);
}

void moveLeftDAS(GameState *gameState) {
    if(!isLeftLegal(gameState)) {
        moveMinoX(gameState->mino, 1);
        correctMinoPos(gameState);
        copyMinoPosition(gameState->mino, gameState->ghostMino);
        softDropGhost(gameState);
        return;
    }
    moveMinoX(gameState->mino, -1);
    moveLeftDAS(gameState);
}

void moveRight(GameState *gameState) {
    moveMinoX(gameState->mino, 1);
    if(!isRightLegal(gameState)) 
        moveMinoX(gameState->mino, -1);
    correctMinoPos(gameState);

    copyMinoPosition(gameState->mino, gameState->ghostMino);
    softDropGhost(gameState);
}

void moveRightDAS(GameState *gameState) {
    if(!isRightLegal(gameState)) {
        moveMinoX(gameState->mino, -1);
        correctMinoPos(gameState);
        copyMinoPosition(gameState->mino, gameState->ghostMino);
        softDropGhost(gameState);
        return;
    }
    moveMinoX(gameState->mino, 1);
    moveRightDAS(gameState);
}

bool isLocationLegal(GameState *gameState) {
    Board *board = gameState->boards->leftBoard;
    Mino *mino = gameState->mino;

    if(
        getBlock(board, mino->anchor->x, mino->anchor->y)->occupied ||
        getBlock(board, mino->block1->x, mino->block1->y)->occupied ||
        getBlock(board, mino->block2->x, mino->block2->y)->occupied ||
        getBlock(board, mino->block3->x, mino->block3->y)->occupied
    ) return false;
    return true;
}

bool isLocationLegalGhost(GameState *gameState) {
    Board *board = gameState->boards->leftBoard;
    Mino *mino = gameState->ghostMino;

    if(
        getBlock(board, mino->anchor->x, mino->anchor->y)->occupied ||
        getBlock(board, mino->block1->x, mino->block1->y)->occupied ||
        getBlock(board, mino->block2->x, mino->block2->y)->occupied ||
        getBlock(board, mino->block3->x, mino->block3->y)->occupied
    ) return false;
    return true;
}

bool isDownLegal(GameState *gameState) {
    Mino *mino = gameState->mino;
    int gridHeight = gameState->settings->GridHeight;

    if(!isLocationLegal(gameState)) return false;
    if(
        mino->anchor->y >= gridHeight ||
        mino->block1->y >= gridHeight ||
        mino->block2->y >= gridHeight ||
        mino->block3->y >= gridHeight
    ) return false;
    return true;
}

bool isDownLegalGhost(GameState *gameState) {
    Mino *mino = gameState->ghostMino;
    int gridHeight = gameState->settings->GridHeight;

    if(!isLocationLegalGhost(gameState)) return false;
    if(
        mino->anchor->y >= gridHeight ||
        mino->block1->y >= gridHeight ||
        mino->block2->y >= gridHeight ||
        mino->block3->y >= gridHeight
    ) return false;
    return true;
}

bool isLeftLegal(GameState *gameState) {
    Mino *mino = gameState->mino;

    if(!isLocationLegal(gameState)) return false;
    if(
        mino->anchor->x < 0 ||
        mino->block1->x < 0 ||
        mino->block2->x < 0 ||
        mino->block3->x < 0
    ) return false;
    return true;
}

bool isRightLegal(GameState *gameState) {
    Mino *mino = gameState->mino;
    int gridWidth = gameState->settings->GridWidth;

    if(!isLocationLegal(gameState)) return false;
    if(
        mino->anchor->x >= gridWidth ||
        mino->block1->x >= gridWidth ||
        mino->block2->x >= gridWidth ||
        mino->block3->x >= gridWidth
    ) return false;
    return true;
}

int clearLines(GameState *gameState) {
    int lineCount = 0;
    Board *board = gameState->boards->leftBoard;
    int width = gameState->settings->GridWidth;
    Color boardColor = gameState->settings->BoardColor;
    for(int i = 0; i < gameState->settings->GridHeight; i++) {
        if(isLineFull(board, width, i)) {
            clearLine(board, width, i, boardColor);
            lineCount++;
        }
    }
    if(lineCount > 0) printf("\ncleared %d lines.", lineCount);
    sendLinesNet(gameState, lineCount);
    return lineCount;
}

void clearLine(Board *board, int width, int row, Color boardColor) {
    for(int i = 0; i < width; i++) {
        getBlock(board, i, row)->occupied = false;
        getBlock(board, i, row)->color = boardColor;
    }
    for(int i = row; i > 0; i--) {
        for(int j = 0; j < width; j++) {
            replaceBlockDown(board, j, i);
        }
    }
    for(int i = 0; i < width; i++) {
        getBlock(board, i, 0)->occupied = false;
        getBlock(board, i, 0)->color = boardColor;
    }
}

bool isLineFull(Board *board, int width, int row) {
    bool occupied = false;
    for(int i = 0; i < width; i++) {
        if(getBlock(board, i, row)->occupied) occupied = true;
        else return false;
    }
    return occupied;
}