#ifndef TETRISLOGIC_H
#define TETRISLOGIC_H

#include "gameState.h"
#include "raylib.h"

void spawnMinoNoDelete(GameState *gameState);
void spawnMino(GameState *gameState);
void spawnGhostMinoNoDelete(GameState *gameState);
void spawnGhostMino(GameState *gameState);

bool isLocationLegal(GameState *gameState);
bool isLocationLegalGhost(GameState *gameState);
bool isLeftLegal(GameState *gameState);
bool isRightLegal(GameState *gameState);
bool isDownLegal(GameState *gameState);
bool isDownLegalGhost(GameState *gameState);

void moveMinoY(Mino *mino, int y);
void moveMinoX(Mino *mino, int x);

void moveLeft(GameState *gameState);
void moveLeftDAS(GameState *gameState);
void moveRight(GameState *gameState);
void moveRightDAS(GameState *gameState);

void hardDrop(GameState *gameState);
void softDrop(GameState *gameState);
void dropMino(GameState *gameState);
void softDropGhost(GameState *gameState);
void dropMinoGhost(GameState *gameState);
void commitMinoToBoard(GameState *gameState);

int clearLines(GameState *gameState);
void clearLine(Board *board, int width, int row, Color boardColor);
bool isLineFull(Board *board, int width, int row);

#endif