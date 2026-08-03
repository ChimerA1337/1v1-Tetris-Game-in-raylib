#include "raylib.h"
#include "../include/block.h"
#include "../include/board.h"
#include <stdlib.h>
//#include <stdio.h>
#include "../include/settings.h"

Board *createBoard(Settings *settings) {
    Block *blocks = malloc(sizeof(Block) * settings->GridWidth * settings->GridHeight);
    // Manually index the 1D array as a 2D array,
    // Use (x + y * xBlocks) to access the block at (x, y) instead of [x][y]

    Board *board = malloc(sizeof(Board));
    board->xBlocks = settings->GridWidth;
    board->yBlocks = settings->GridHeight;

    board->startX = settings->StartX;
    board->startY = settings->StartY;
    board->blocks = blocks;

    Block *block;
    for(int i = 0; i < settings->GridWidth; i++) {
        for (int j = 0; j < settings->GridHeight; j++) {
            block = getBlock(board, i, j);
            *block = createBlock(settings, i, j);
        }
    }
    return board;
}

Board *createRightBoard(Settings *settings) {
    Block *blocks = malloc(sizeof(Block) * settings->GridWidth * settings->GridHeight);
    // Manually index the 1D array as a 2D array,
    // Use (x + y * xBlocks) to access the block at (x, y) instead of [x][y]

    Board *board = malloc(sizeof(Board));
    board->xBlocks = settings->GridWidth;
    board->yBlocks = settings->GridHeight;

    board->startX = settings->StartX+800;
    board->startY = settings->StartY;
    board->blocks = blocks;

    Block *block;
    for(int i = 0; i < settings->GridWidth; i++) {
        for (int j = 0; j < settings->GridHeight; j++) {
            block = getBlock(board, i, j);
            *block = createBlockRight(settings, i, j);
        }
    }
    return board;
}

Boards *createBoards(Settings *settings) {
    Boards *boards = malloc(sizeof(Boards));
    boards->leftBoard = createBoard(settings);
    boards->rightBoard = createRightBoard(settings);
    return boards;
}

void freeBoard(Board *board) {
    free(board->blocks);
    free(board);
}

void freeBoards(Boards *boards) {
    freeBoard(boards->leftBoard);
    freeBoard(boards->rightBoard);
    free(boards);
}

void drawBoard(Board *board, Settings *settings) {
    for(int i = 0; i < board->xBlocks; i++)
        for (int j = 0; j < board->yBlocks; j++)
            drawBlock(getBlock(board, i, j), settings);

    Rectangle boardOutline = {
        board->startX - settings->BoardlineThickness,
        board->startY - settings->BoardlineThickness,
        settings->BlockSize * board->xBlocks + 2*settings->BoardlineThickness,
        settings->BlockSize * board->yBlocks + 2*settings->BoardlineThickness
    };
    DrawRectangleLinesEx(boardOutline, settings->BoardlineThickness, settings->BoardEdgeColor);
}

void drawBoards(Boards *boards, Settings *settings) {
    drawBoard(boards->leftBoard, settings);
    drawBoard(boards->rightBoard, settings);
}