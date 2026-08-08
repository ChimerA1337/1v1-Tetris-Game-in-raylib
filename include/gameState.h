#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "board.h"
#include "randomizer.h"
#include <stdbool.h>
#include "menu.h"
#include "network.h"

typedef struct Tetrimino Mino;
typedef struct Settings Settings;
typedef struct NetworkState NetworkState;
typedef struct PreviewColumn PreviewCol;
typedef struct Hold Hold;

typedef struct GameState {
    Boards *boards;
    Bags *bags;
    Mino *mino;
    Mino *ghostMino;
    bool paused;
    float DAStimer;
    PreviewCol *previewCol;
    PreviewCol *rightPreviewCol;
    Hold *hold;
    Hold *rightHold;
    MenuState *menuState;
    NetworkState *networkState;
    Settings *settings;
} GameState;

GameState *createGameState();
void freeGameState(GameState *gameState);

#endif