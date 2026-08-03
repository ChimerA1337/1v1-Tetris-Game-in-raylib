#include "../include/input.h"
#include "../include/raylib.h"
#include "../include/gameState.h"
#include "../include/minos.h"
#include "../include/tetrisLogic.h"
#include "../include/rotation.h"
#include "../include/settings.h"
#include "../include/hold.h"
//#include <stdio.h>

void handleInput(GameState *gameState, Settings *settings) {
    if(IsKeyPressed(settings->HardDrop)) spawnMino(gameState, settings);
    if(IsKeyPressed(settings->SoftDrop)) softDrop(gameState, settings);
    if(IsKeyPressed(settings->Hold)) hold(gameState, settings);

    if(IsKeyPressed(settings->MoveLeft)) moveLeft(gameState, settings);
    else if(IsKeyDown(settings->MoveLeft)) {
        gameState->DAStimer += GetFrameTime();
        if(gameState->DAStimer >= settings->Das) moveLeftDAS(gameState, settings);
    }
    else if(IsKeyUp(settings->MoveRight)) gameState->DAStimer = 0;

    
    if(IsKeyPressed(settings->MoveRight)) moveRight(gameState, settings);
    else if(IsKeyDown(settings->MoveRight)) {
        gameState->DAStimer += GetFrameTime();
        if(gameState->DAStimer >= settings->Das) moveRightDAS(gameState, settings);
    }
    else if(IsKeyUp(settings->MoveLeft)) gameState->DAStimer = 0;
    
    if(IsKeyPressed(settings->RotateLeft)) rotateLeft(gameState, settings);
    if(IsKeyPressed(settings->RotateRight)) rotateRight(gameState, settings);
}