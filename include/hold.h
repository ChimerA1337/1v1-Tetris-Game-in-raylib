#ifndef HOLD_H
#define HOLD_H

#include "raylib.h"
#include "minos.h"

typedef struct Hold {
    Rectangle rect;
    MinoType minoType;
    bool hasMino;
} Hold;

Hold *createHold(Settings *settings);
void drawHold(GameState *gameState, Settings *settings);

void hold(GameState *gameState, Settings *settings);
void holdNoMino(GameState *gameState, Settings *settings);

#endif