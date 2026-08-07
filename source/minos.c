#include "raylib.h"
#include "../include/block.h"
#include "../include/minos.h"
#include <stdlib.h>
#include "../include/gameState.h"

Mino *spawnI(Board *board) {
    Mino *mino = malloc(sizeof(Mino));
    mino->block1 = copyBlock(board, 3, 1);
    mino->anchor = copyBlock(board, 4, 1);
    mino->block2 = copyBlock(board, 5, 1);
    mino->block3 = copyBlock(board, 6, 1);
    mino->minoType = MinoI;
    mino->rotation = ROT_0;
    mino->color = SKYBLUE;
    return mino;
}
Mino *spawnO(Board *board) {
    Mino *mino = malloc(sizeof(Mino));
    mino->block1 = copyBlock(board, 4, 1);
    mino->block2 = copyBlock(board, 5, 1);
    mino->anchor = copyBlock(board, 4, 2);
    mino->block3 = copyBlock(board, 5, 2);
    mino->minoType = MinoO;
    mino->rotation = ROT_0;
    mino->color = YELLOW;
    return mino;
}
Mino *spawnT(Board *board) {
    Mino *mino = malloc(sizeof(Mino));
    mino->block1 = copyBlock(board, 3, 2);
    mino->anchor = copyBlock(board, 4, 2);
    mino->block2 = copyBlock(board, 5, 2);
    mino->block3 = copyBlock(board, 4, 1);
    mino->minoType = MinoT;
    mino->rotation = ROT_0;
    mino->color = PURPLE;
    return mino;
}
Mino *spawnL(Board *board) {
    Mino *mino = malloc(sizeof(Mino));
    mino->block1 = copyBlock(board, 3, 2);
    mino->anchor = copyBlock(board, 4, 2);
    mino->block2 = copyBlock(board, 5, 2);
    mino->block3 = copyBlock(board, 5, 1);
    mino->minoType = MinoL;
    mino->rotation = ROT_0;
    mino->color = ORANGE;
    return mino;
}
Mino *spawnJ(Board *board) {
    Mino *mino = malloc(sizeof(Mino));
    mino->block1 = copyBlock(board, 3, 1);
    mino->block2 = copyBlock(board, 3, 2);
    mino->anchor = copyBlock(board, 4, 2);
    mino->block3 = copyBlock(board, 5, 2);
    mino->minoType = MinoJ;
    mino->rotation = ROT_0;
    mino->color = DARKBLUE;
    return mino;
}
Mino *spawnS(Board *board) {
    Mino *mino = malloc(sizeof(Mino));
    mino->block1 = copyBlock(board, 3, 2);
    mino->anchor = copyBlock(board, 4, 2);
    mino->block2 = copyBlock(board, 4, 1);
    mino->block3 = copyBlock(board, 5, 1);
    mino->minoType = MinoS;
    mino->rotation = ROT_0;
    mino->color = GREEN;
    return mino;
}
Mino *spawnZ(Board *board) {
    Mino *mino = malloc(sizeof(Mino));
    mino->block1 = copyBlock(board, 3, 1);
    mino->block2 = copyBlock(board, 4, 1);
    mino->anchor = copyBlock(board, 4, 2);
    mino->block3 = copyBlock(board, 5, 2);
    mino->minoType = MinoZ;
    mino->rotation = ROT_0;
    mino->color = RED;
    return mino;
}

Mino *copyMino(Mino *mino) {
    Mino *copiedMino = malloc(sizeof(Mino));
    copiedMino->anchor = copyBlockFromBlock(mino->anchor);
    copiedMino->block1 = copyBlockFromBlock(mino->block1);
    copiedMino->block2 = copyBlockFromBlock(mino->block2);
    copiedMino->block3 = copyBlockFromBlock(mino->block3);
    copiedMino->minoType = mino->minoType;
    copiedMino->rotation = mino->rotation;
    copiedMino->color = mino->color;
    return copiedMino;
}

void copyMinoPosition(Mino *from, Mino *to) {
    to->anchor->x = from->anchor->x; to->anchor->y = from->anchor->y;
    to->block1->x = from->block1->x; to->block1->y = from->block1->y;
    to->block2->x = from->block2->x; to->block2->y = from->block2->y;
    to->block3->x = from->block3->x; to->block3->y = from->block3->y;
}

void freeMino(Mino *mino) {
    freeBlock(mino->anchor);
    freeBlock(mino->block1);
    freeBlock(mino->block2);
    freeBlock(mino->block3);
    free(mino);
}

void drawMino(Mino *mino, Settings *settings) {
    mino->anchor->color = mino->color;
    mino->block1->color = mino->color;
    mino->block2->color = mino->color;
    mino->block3->color = mino->color;

    drawBlock(mino->anchor, settings);
    drawBlock(mino->block1, settings);
    drawBlock(mino->block2, settings);
    drawBlock(mino->block3, settings);
}

void clearMino(Mino *mino, Color boardColor) {
    mino->anchor->color = boardColor;
    mino->block1->color = boardColor;
    mino->block2->color = boardColor;
    mino->block3->color = boardColor;
}

void correctMinoPos(GameState *gameState) {
    int blockSize = gameState->settings->BlockSize;
    correctBlockPos(gameState->boards->leftBoard, gameState->mino->anchor, blockSize);
    correctBlockPos(gameState->boards->leftBoard, gameState->mino->block1, blockSize);
    correctBlockPos(gameState->boards->leftBoard, gameState->mino->block2, blockSize);
    correctBlockPos(gameState->boards->leftBoard, gameState->mino->block3, blockSize);
}

void correctMinoPosGhost(GameState *gameState) {
    int blockSize = gameState->settings->BlockSize;
    correctBlockPos(gameState->boards->leftBoard, gameState->ghostMino->anchor, blockSize);
    correctBlockPos(gameState->boards->leftBoard, gameState->ghostMino->block1, blockSize);
    correctBlockPos(gameState->boards->leftBoard, gameState->ghostMino->block2, blockSize);
    correctBlockPos(gameState->boards->leftBoard, gameState->ghostMino->block3, blockSize);
}

