#ifndef MINOS_H
#define MINOS_H

#include "board.h"
#include "raylib.h"
#include "definitions.h"
#include "rotation.h"
#include "settings.h"

typedef struct GameState GameState;
typedef struct Block Block;
typedef struct Settings Settings;
typedef enum Rotation Rotation;

typedef enum MinoType {
    MinoI,
    MinoO,
    MinoT,
    MinoL,
    MinoJ,
    MinoS,
    MinoZ
} MinoType;

typedef struct Tetrimino {
    Block *anchor;
    Block *block1;
    Block *block2;
    Block *block3;
    MinoType minoType;
    Color color;
    Rotation rotation;

    //void (*draw) (struct Tetrimino *self);
} Mino;

Mino *spawnI(Board *board);
Mino *spawnO(Board *board);
Mino *spawnT(Board *board);
Mino *spawnL(Board *board);
Mino *spawnJ(Board *board);
Mino *spawnS(Board *board);
Mino *spawnZ(Board *board);

Mino *copyMino(Mino *mino);
void copyMinoPosition(Mino *from, Mino *to);
void freeMino(Mino *mino);

void drawMino(Mino *mino, Settings *settings);
void clearMino(Mino *mino, Color boardColor);

void correctMinoPos(GameState *gameState);
void correctMinoPosGhost(GameState *gameState);

Color getMinoColor(MinoType type);

#endif