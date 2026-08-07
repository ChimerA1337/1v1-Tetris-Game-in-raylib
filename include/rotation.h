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

bool isRotationLegal(GameState *gameState);

void rotateLeft(GameState *gameState);
void rotateRight(GameState *gameState);
void rotate180(GameState *gameState);

void rotateLeftJLTSZ(GameState *gameState);
void rotateLeftI(GameState *gameState);

void rotateRightJLTSZ(GameState *gameState);
void rotateRightI(GameState *gameState);

bool leftTestsJLTSZRot0(GameState *gameState);
bool leftTestsJLTSZRotR(GameState *gameState);
bool leftTestsJLTSZRot2(GameState *gameState);
bool leftTestsJLTSZRotL(GameState *gameState);
bool leftTestsIRot0(GameState *gameState);
bool leftTestsIRotR(GameState *gameState);
bool leftTestsIRot2(GameState *gameState);
bool leftTestsIRotL(GameState *gameState);

bool rightTestsJLTSZRot0(GameState *gameState);
bool rightTestsJLTSZRotR(GameState *gameState);
bool rightTestsJLTSZRot2(GameState *gameState);
bool rightTestsJLTSZRotL(GameState *gameState);
bool rightTestsIRot0(GameState *gameState);
bool rightTestsIRotR(GameState *gameState);
bool rightTestsIRot2(GameState *gameState);
bool rightTestsIRotL(GameState *gameState);

#endif
