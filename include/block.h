#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"

typedef struct Block {
    Rectangle rect;
    Color color;
    int x;
    int y;
    bool occupied;

    void (*draw) (struct Block *self);
} Block;

typedef struct Board Board;
typedef struct Settings Settings;
typedef struct GameState GameState;

Block *getBlock(Board *board, int x, int y);
Block *copyBlock(Board *board, int x, int y);
void replaceBlock(Board *board, int x, int y);
Block *copyBlockFromBlock(Block *block);
void freeBlock(Block *block);
Block createBlock(Settings *settings, int i, int j);
void drawBlock(Block *block, Settings *settings);
void correctBlockPos(Board *board, Block *block, int blockSize);

Block createBlockRight(Settings *settings, int i, int j);

#endif