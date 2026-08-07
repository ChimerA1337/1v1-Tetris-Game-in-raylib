#include "../include/input.h"
#include "../include/raylib.h"
#include "../include/gameState.h"
#include "../include/minos.h"
#include "../include/tetrisLogic.h"
#include "../include/rotation.h"
#include "../include/settings.h"
#include "../include/hold.h"
#include "../include/network.h"
//#include <stdio.h>

void handleInput(GameState *gameState) {
    Settings *settings = gameState->settings;
    if(IsKeyPressed(settings->HardDrop)) {
        spawnMino(gameState);
        sendBoardState(gameState);
    }
    if(IsKeyPressed(settings->SoftDrop)) softDrop(gameState);
    if(IsKeyPressed(settings->Hold)) hold(gameState);

    if(IsKeyPressed(settings->MoveLeft)) moveLeft(gameState);
    else if(IsKeyDown(settings->MoveLeft)) {
        gameState->DAStimer += GetFrameTime();
        if(gameState->DAStimer >= settings->Das) moveLeftDAS(gameState);
    }
    else if(IsKeyUp(settings->MoveRight)) gameState->DAStimer = 0;

    
    if(IsKeyPressed(settings->MoveRight)) moveRight(gameState);
    else if(IsKeyDown(settings->MoveRight)) {
        gameState->DAStimer += GetFrameTime();
        if(gameState->DAStimer >= settings->Das) moveRightDAS(gameState);
    }
    else if(IsKeyUp(settings->MoveLeft)) gameState->DAStimer = 0;
    
    if(IsKeyPressed(settings->RotateLeft)) rotateLeft(gameState);
    if(IsKeyPressed(settings->RotateRight)) rotateRight(gameState);
}