#ifndef TETRISLOGIC_H
#define TETRISLOGIC_H

#include "gameState.h"
#include "raylib.h"

void spawnMinoNoDelete(GameState *gameState, Settings *settings);
void spawnMino(GameState *gameState, Settings *settings);
void spawnGhostMinoNoDelete(GameState *gameState, Settings *settings);
void spawnGhostMino(GameState *gameState, Settings *settings);

bool isLocationLegal(GameState *gameState);
bool isLocationLegalGhost(GameState *gameState);
bool isLeftLegal(GameState *gameState);
bool isRightLegal(GameState *gameState, int gridWidth);
bool isDownLegal(GameState *gameState, int gridHeight);
bool isDownLegalGhost(GameState *gameState, int gridHeight);

void moveMinoY(Mino *mino, int y);
void moveMinoX(Mino *mino, int x);

void moveLeft(GameState *gameState, Settings *settings);
void moveLeftDAS(GameState *gameState, Settings *settings);
void moveRight(GameState *gameState, Settings *settings);
void moveRightDAS(GameState *gameState, Settings *settings);

void hardDrop(GameState *gameState, Settings *settings);
void softDrop(GameState *gameState, Settings *settings);
void dropMino(GameState *gameState, Settings *settings);
void softDropGhost(GameState *gameState, Settings *settings);
void dropMinoGhost(GameState *gameState, Settings *settings);
void commitMinoToBoard(GameState *gameState);

void clearLines(GameState *gameState, Settings *settings);
void clearLine(Board *board, int width, int row, Color boardColor);
bool isLineFull(Board *board, int width, int row);

#endif