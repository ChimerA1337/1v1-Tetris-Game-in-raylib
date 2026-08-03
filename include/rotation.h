#ifndef ROTATION_H
#define ROTATION_H

#include "gameState.h"

typedef enum Rotation {
    ROT_0,
    ROT_R,
    ROT_2,
    ROT_L
} Rotation;

void rotateLeftMinoJ(Mino *mino);
void rotateLeftMinoL(Mino *mino);
void rotateLeftMinoT(Mino *mino);
void rotateLeftMinoS(Mino *mino);
void rotateLeftMinoZ(Mino *mino);
void rotateLeftMinoI(Mino *mino);

void rotateRightMinoJ(Mino *mino);
void rotateRightMinoL(Mino *mino);
void rotateRightMinoT(Mino *mino);
void rotateRightMinoS(Mino *mino);
void rotateRightMinoZ(Mino *mino);
void rotateRightMinoI(Mino *mino);

bool isRotationLegal(GameState *gameState, Settings *settings);

void rotateLeft(GameState *gameState, Settings *settings);
void rotateRight(GameState *gameState, Settings *settings);
void rotate180(GameState *gameState, Settings *settings);

void rotateLeftJLTSZ(GameState *gameState, Settings *settings);
void rotateLeftI(GameState *gameState, Settings *settings);

void rotateRightJLTSZ(GameState *gameState, Settings *settings);
void rotateRightI(GameState *gameState, Settings *settings);

bool leftTestsJLTSZRot0(GameState *gameState, Settings *settings);
bool leftTestsJLTSZRotR(GameState *gameState, Settings *settings);
bool leftTestsJLTSZRot2(GameState *gameState, Settings *settings);
bool leftTestsJLTSZRotL(GameState *gameState, Settings *settings);
bool leftTestsIRot0(GameState *gameState, Settings *settings);
bool leftTestsIRotR(GameState *gameState, Settings *settings);
bool leftTestsIRot2(GameState *gameState, Settings *settings);
bool leftTestsIRotL(GameState *gameState, Settings *settings);

bool rightTestsJLTSZRot0(GameState *gameState, Settings *settings);
bool rightTestsJLTSZRotR(GameState *gameState, Settings *settings);
bool rightTestsJLTSZRot2(GameState *gameState, Settings *settings);
bool rightTestsJLTSZRotL(GameState *gameState, Settings *settings);
bool rightTestsIRot0(GameState *gameState, Settings *settings);
bool rightTestsIRotR(GameState *gameState, Settings *settings);
bool rightTestsIRot2(GameState *gameState, Settings *settings);
bool rightTestsIRotL(GameState *gameState, Settings *settings);

#endif
