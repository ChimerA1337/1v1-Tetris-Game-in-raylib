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
void drawHold(GameState *gameState);

void hold(GameState *gameState);
void holdNoMino(GameState *gameState);

#endif