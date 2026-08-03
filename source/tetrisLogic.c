#include "../include/gameState.h"
#include <stdio.h>
#include "../include/tetrisLogic.h"
#include "../include/block.h"
#include "../include/minos.h"
#include "../include/settings.h"
#include "../include/preview.h"
#include "../include/definitions.h"

void spawnMinoNoDelete(GameState *gameState, Settings *settings) {
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

void spawnMino(GameState *gameState, Settings *settings) {
    hardDrop(gameState, settings);
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
            spawnMinoNoDelete(gameState, settings);
            break;
        default:
            printf("\nbag gave a mino out of scope. ");
    }
    updatePreviewCol(gameState->previewCol, gameState->bags);
    spawnGhostMino(gameState, settings);
}

void spawnGhostMinoNoDelete(GameState *gameState, Settings *settings) {
    Mino *ghostMino = copyMino(gameState->mino);

    ghostMino->color = ColorAlpha(ghostMino->color, settings->GhostMinoAlpha);

    gameState->ghostMino = ghostMino;
    softDropGhost(gameState, settings);
}

void spawnGhostMino(GameState *gameState, Settings *settings) {
    Mino *ghostMino = copyMino(gameState->mino);
    clearMino(gameState->ghostMino, settings->BoardColor);
    freeMino(gameState->ghostMino);

    ghostMino->color = ColorAlpha(ghostMino->color, settings->GhostMinoAlpha);

    gameState->ghostMino = ghostMino;
    softDropGhost(gameState, settings);
}

void hardDrop(GameState *gameState, Settings *settings) {
    softDrop(gameState, settings);
    commitMinoToBoard(gameState);
    clearLines(gameState, settings);
}

void softDrop(GameState *gameState, Settings *settings) {
    dropMino(gameState, settings);
    correctMinoPos(gameState, settings->BlockSize);
}

void dropMino(GameState *gameState, Settings *settings) {
    if(!isDownLegal(gameState, settings->GridHeight)) {
        moveMinoY(gameState->mino, -1);
        return;
    }
    moveMinoY(gameState->mino, 1);
    dropMino(gameState, settings);
}

void softDropGhost(GameState *gameState, Settings *settings) {
    dropMinoGhost(gameState, settings);
    correctMinoPosGhost(gameState, settings->BlockSize);
}

void dropMinoGhost(GameState *gameState, Settings *settings) {
    if(!isDownLegalGhost(gameState, settings->GridHeight)) {
        moveMinoY(gameState->ghostMino, -1);
        return;
    }
    moveMinoY(gameState->ghostMino, 1);
    dropMinoGhost(gameState, settings);
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

void moveLeft(GameState *gameState, Settings *settings) {
    moveMinoX(gameState->mino, -1);
    if(!isLeftLegal(gameState))
        moveMinoX(gameState->mino, 1);
    correctMinoPos(gameState, settings->BlockSize);

    copyMinoPosition(gameState->mino, gameState->ghostMino);
    softDropGhost(gameState, settings);
}

void moveLeftDAS(GameState *gameState, Settings *settings) {
    if(!isLeftLegal(gameState)) {
        moveMinoX(gameState->mino, 1);
        correctMinoPos(gameState, settings->BlockSize);
        copyMinoPosition(gameState->mino, gameState->ghostMino);
        softDropGhost(gameState, settings);
        return;
    }
    moveMinoX(gameState->mino, -1);
    moveLeftDAS(gameState, settings);
}

void moveRight(GameState *gameState, Settings *settings) {
    moveMinoX(gameState->mino, 1);
    if(!isRightLegal(gameState, settings->GridWidth)) 
        moveMinoX(gameState->mino, -1);
    correctMinoPos(gameState, settings->BlockSize);

    copyMinoPosition(gameState->mino, gameState->ghostMino);
    softDropGhost(gameState, settings);
}

void moveRightDAS(GameState *gameState, Settings *settings) {
    if(!isRightLegal(gameState, settings->GridWidth)) {
        moveMinoX(gameState->mino, -1);
        correctMinoPos(gameState, settings->BlockSize);
        copyMinoPosition(gameState->mino, gameState->ghostMino);
        softDropGhost(gameState, settings);
        return;
    }
    moveMinoX(gameState->mino, 1);
    moveRightDAS(gameState, settings);
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

bool isDownLegal(GameState *gameState, int gridHeight) {
    Mino *mino = gameState->mino;

    if(!isLocationLegal(gameState)) return false;
    if(
        mino->anchor->y >= gridHeight ||
        mino->block1->y >= gridHeight ||
        mino->block2->y >= gridHeight ||
        mino->block3->y >= gridHeight
    ) return false;
    return true;
}

bool isDownLegalGhost(GameState *gameState, int gridHeight) {
    Mino *mino = gameState->ghostMino;

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

bool isRightLegal(GameState *gameState, int gridWidth) {
    Mino *mino = gameState->mino;

    if(!isLocationLegal(gameState)) return false;
    if(
        mino->anchor->x >= gridWidth ||
        mino->block1->x >= gridWidth ||
        mino->block2->x >= gridWidth ||
        mino->block3->x >= gridWidth
    ) return false;
    return true;
}

void clearLines(GameState *gameState, Settings *settings) {
    Board *board = gameState->boards->leftBoard;
    int width = settings->GridWidth;
    Color boardColor = settings->BoardColor;
    for(int i = 0; i < settings->GridHeight; i++) {
        if(isLineFull(board, width, i)) 
            clearLine(board, width, i, boardColor);
    }
}

void clearLine(Board *board, int width, int row, Color boardColor) {
    for(int i = 0; i < width; i++) {
        getBlock(board, i, row)->occupied = false;
        getBlock(board, i, row)->color = boardColor;
    }
    for(int i = row; i > 0; i--) {
        for(int j = 0; j < width; j++) {
            replaceBlock(board, j, i);
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