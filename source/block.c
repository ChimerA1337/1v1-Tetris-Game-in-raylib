#include "raylib.h"
#include "../include/block.h"
#include "../include/board.h"
#include <stdlib.h>
#include "../include/settings.h"


Block createBlock(Settings *settings, int i, int j) {
    Block block;
    block.x = i;
    block.y = j;
    block.rect.x = settings->BlockSize * block.x + settings->StartX;
    block.rect.y = settings->BlockSize * block.y + settings->StartY;
    block.rect.width = settings->BlockSize;
    block.rect.height = settings->BlockSize;
    block.color = settings->BoardColor;
    block.occupied = false;
    return block;
}

Block createBlockRight(Settings *settings, int i, int j) {
    Block block;
    block.x = i;
    block.y = j;
    block.rect.x = settings->BlockSize * block.x + settings->StartX+800;
    block.rect.y = settings->BlockSize * block.y + settings->StartY;
    block.rect.width = settings->BlockSize;
    block.rect.height = settings->BlockSize;
    block.color = settings->BoardColor;
    block.occupied = false;
    return block;
}


Block *getBlock(Board *board, int x, int y) {
    return &board->blocks[x + y * board->xBlocks];
}

Block *copyBlock(Board *board, int x, int y) {
    Block block = board->blocks[x + y * board->xBlocks];
    Block *returnBlock = malloc(sizeof(Block));
    *returnBlock = block;
    return returnBlock;
}

void replaceBlock(Board *board, int x, int y) {
    Block *block = &board->blocks[x + y * board->xBlocks];

    block->color = board->blocks[x + (y-1) * board->xBlocks].color;
    block->occupied = board->blocks[x + (y-1) * board->xBlocks].occupied;
}

Block *copyBlockFromBlock(Block *block) {
    Block *returnBlock = malloc(sizeof(Block));
    *returnBlock = *block;
    return returnBlock;
}

void freeBlock(Block *block) {
    free(block);
}

void drawBlock(Block *block, Settings *settings) {
    DrawRectangleRec(block->rect, block->color);
    DrawRectangleLinesEx(block->rect, settings->OutlineThickness, settings->OutlineColor);
}

void setBlockColor(Block *block, Color color) {
    block->color = color;
}

void correctBlockPos(Board *board, Block *block, int blockSize) {
    block->rect.x = blockSize * block->x + board->startX;
    block->rect.y = blockSize * block->y + board->startY;
}