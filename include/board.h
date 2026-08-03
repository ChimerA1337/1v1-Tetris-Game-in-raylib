#ifndef BOARD_H
#define BOARD_H

#include "raylib.h"

//typedef struct GameState GameState;
typedef struct Block Block;
typedef struct Tetrimino Mino;
typedef struct Settings Settings;
typedef struct Bags Bags;

typedef struct Board {
    int xBlocks;
    int yBlocks;
    int startX;
    int startY;
    Block *blocks;
} Board;

typedef struct Boards { // Might add more than 2 players in the future
    Board *leftBoard;
    Board *rightBoard;
} Boards;

Board *createBoard(Settings *settings);
Board *createRightBoard(Settings *settings);
void freeBoard(Board *board);

// Load a save .json file later with all the preferred settings on the boards, for now hardcoded
Boards *createBoards(Settings *settings);
void freeBoards(Boards *boards);

void drawBoard(Board *board, Settings *settings);
void drawBoards(Boards *boards, Settings *settings);

#endif