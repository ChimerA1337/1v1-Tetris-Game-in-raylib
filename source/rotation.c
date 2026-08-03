#include "../include/rotation.h"
#include "../include/tetrisLogic.h"
#include <stdio.h>
#include "../include/block.h"
#include "../include/minos.h"
#include "../include/settings.h"

void rotateLeftMinoJ(Mino *mino) {
    switch(mino->rotation) {
        case ROT_0:
            mino->block1->y+=2;
            mino->block2->x++; mino->block2->y++;
            mino->block3->x--; mino->block3->y--;
            break;
        case ROT_R:
            mino->block1->x-=2;
            mino->block2->x--; mino->block2->y++;
            mino->block3->x++; mino->block3->y--;
            break;
        case ROT_2:
            mino->block1->y-=2;
            mino->block2->x--; mino->block2->y--;
            mino->block3->x++; mino->block3->y++;
            break;
        case ROT_L:
            mino->block1->x+=2;
            mino->block2->x++; mino->block2->y--;
            mino->block3->x--; mino->block3->y++;
            break;
        default:
            printf("No such rotation?");
    }
}
void rotateLeftMinoL(Mino *mino) {
    switch(mino->rotation) {
        case ROT_0:
            mino->block1->x++; mino->block1->y++;
            mino->block2->x--; mino->block2->y--;
            mino->block3->x-=2;
            break;
        case ROT_R:
            mino->block1->x--; mino->block1->y++;
            mino->block2->x++; mino->block2->y--;
            mino->block3->y-=2;
            break;
        case ROT_2:
            mino->block1->x--; mino->block1->y--;
            mino->block2->x++; mino->block2->y++;
            mino->block3->x+=2;
            break;
        case ROT_L:
            mino->block1->x++; mino->block1->y--;
            mino->block2->x--; mino->block2->y++;
            mino->block3->y+=2;
            break;
        default:
            printf("No such rotation?");
    }
}

void rotateLeftMinoT(Mino *mino) {
    switch(mino->rotation) {
        case ROT_0:
            mino->block1->x++; mino->block1->y++;
            mino->block2->x--; mino->block2->y--;
            mino->block3->x--; mino->block3->y++;
            break;
        case ROT_R:
            mino->block1->x--; mino->block1->y++;
            mino->block2->x++; mino->block2->y--;
            mino->block3->x--; mino->block3->y--;
            break;
        case ROT_2:
            mino->block1->x--; mino->block1->y--;
            mino->block2->x++; mino->block2->y++;
            mino->block3->x++; mino->block3->y--;
            break;
        case ROT_L:
            mino->block1->x++; mino->block1->y--;
            mino->block2->x--; mino->block2->y++;
            mino->block3->x++; mino->block3->y++;
            break;
        default:
            printf("No such rotation?");
    }
}

void rotateLeftMinoS(Mino *mino) {
    switch(mino->rotation) {
        case ROT_0:
            mino->block1->x++; mino->block1->y++;
            mino->block2->x--; mino->block2->y++;
            mino->block3->x-=2;
            break;
        case ROT_R:
            mino->block1->x--; mino->block1->y++;
            mino->block2->x--; mino->block2->y--;
            mino->block3->y-=2;
            break;
        case ROT_2:
            mino->block1->x--; mino->block1->y--;
            mino->block2->x++; mino->block2->y--;
            mino->block3->x+=2;
            break;
        case ROT_L:
            mino->block1->x++; mino->block1->y--;
            mino->block2->x++; mino->block2->y++;
            mino->block3->y+=2;
            break;
        default:
            printf("No such rotation?");
    }
}
void rotateLeftMinoZ(Mino *mino) {
    switch(mino->rotation) {
        case ROT_0:
            mino->block1->y+=2;
            mino->block2->x--; mino->block2->y++;
            mino->block3->x--; mino->block3->y--;
            break;
        case ROT_R:
            mino->block1->x-=2;
            mino->block2->x--; mino->block2->y--;
            mino->block3->x++; mino->block3->y--;
            break;
        case ROT_2:
            mino->block1->y-=2;
            mino->block2->x++; mino->block2->y--;
            mino->block3->x++; mino->block3->y++;
            break;
        case ROT_L:
            mino->block1->x+=2;
            mino->block2->x++; mino->block2->y++;
            mino->block3->x--; mino->block3->y++;
            break;
        default:
            printf("No such rotation?");
    }
}

void rotateLeftMinoI(Mino *mino) {
    switch(mino->rotation) {
        case ROT_0:
            mino->block1->x++; mino->block1->y+=2;
            mino->anchor->y++;
            mino->block2->x--;
            mino->block3->x-=2; mino->block3->y--;
            break;
        case ROT_R:
            mino->block1->x-=2; mino->block1->y++;
            mino->anchor->x--;
            mino->block2->y--;
            mino->block3->x++; mino->block3->y-=2;
            break;
        case ROT_2:
            mino->block1->x--; mino->block1->y-=2;
            mino->anchor->y--;
            mino->block2->x++;
            mino->block3->x+=2; mino->block3->y++;
            break;
        case ROT_L:
            mino->block1->x+=2; mino->block1->y--;
            mino->anchor->x++;
            mino->block2->y++;
            mino->block3->x--; mino->block3->y+=2;
            break;
        default:
            printf("No such rotation?");
    }
}

void rotateRightMinoJ(Mino *mino) {
    switch(mino->rotation) {
        case ROT_0:
            mino->block1->x+=2;
            mino->block2->x++; mino->block2->y--;
            mino->block3->x--; mino->block3->y++;
            break;
        case ROT_R:
            mino->block1->y+=2;
            mino->block2->x++; mino->block2->y++;
            mino->block3->x--; mino->block3->y--;
            break;
        case ROT_2:
            mino->block1->x-=2;
            mino->block2->x--; mino->block2->y++;
            mino->block3->x++; mino->block3->y--;
            break;
        case ROT_L:
            mino->block1->y-=2;
            mino->block2->x--; mino->block2->y--;
            mino->block3->x++; mino->block3->y++;
            break;
        default:
            printf("No such rotation?");
    }
}
void rotateRightMinoL(Mino *mino) {
    switch(mino->rotation) {
        case ROT_0:
            mino->block1->x++; mino->block1->y--;
            mino->block2->x--; mino->block2->y++;
            mino->block3->y+=2;
            break;
        case ROT_R:
            mino->block1->x++; mino->block1->y++;
            mino->block2->x--; mino->block2->y--;
            mino->block3->x-=2;
            break;
        case ROT_2:
            mino->block1->x--; mino->block1->y++;
            mino->block2->x++; mino->block2->y--;
            mino->block3->y-=2;
            break;
        case ROT_L:
            mino->block1->x--; mino->block1->y--;
            mino->block2->x++; mino->block2->y++;
            mino->block3->x+=2;
            break;
        default:
            printf("No such rotation?");
    }
}
void rotateRightMinoT(Mino *mino) {
    switch(mino->rotation) {
        case ROT_0:
            mino->block1->x++; mino->block1->y--;
            mino->block2->x--; mino->block2->y++;
            mino->block3->x++; mino->block3->y++;
            break;
        case ROT_R:
            mino->block1->x++; mino->block1->y++;
            mino->block2->x--; mino->block2->y--;
            mino->block3->x--; mino->block3->y++;
            break;
        case ROT_2:
            mino->block1->x--; mino->block1->y++;
            mino->block2->x++; mino->block2->y--;
            mino->block3->x--; mino->block3->y--;
            break;
        case ROT_L:
            mino->block1->x--; mino->block1->y--;
            mino->block2->x++; mino->block2->y++;
            mino->block3->x++; mino->block3->y--;
            break;
        default:
            printf("No such rotation?");
    }
}
void rotateRightMinoS(Mino *mino) {
    switch(mino->rotation) {
        case ROT_0:
            mino->block1->x++; mino->block1->y--;
            mino->block2->x++; mino->block2->y++;
            mino->block3->y+=2;
            break;
        case ROT_R:
            mino->block1->x++; mino->block1->y++;
            mino->block2->x--; mino->block2->y++;
            mino->block3->x-=2;
            break;
        case ROT_2:
            mino->block1->x--; mino->block1->y++;
            mino->block2->x--; mino->block2->y--;
            mino->block3->y-=2;
            break;
        case ROT_L:
            mino->block1->x--; mino->block1->y--;
            mino->block2->x++; mino->block2->y--;
            mino->block3->x+=2;
            break;
        default:
            printf("No such rotation?");
    }
}
void rotateRightMinoZ(Mino *mino) {
    switch(mino->rotation) {
        case ROT_0:
            mino->block1->x+=2;
            mino->block2->x++; mino->block2->y++;
            mino->block3->x--; mino->block3->y++;
            break;
        case ROT_R:
            mino->block1->y+=2;
            mino->block2->x--; mino->block2->y++;
            mino->block3->x--; mino->block3->y--;
            break;
        case ROT_2:
            mino->block1->x-=2;
            mino->block2->x--; mino->block2->y--;
            mino->block3->x++; mino->block3->y--;
            break;
        case ROT_L:
            mino->block1->y-=2;
            mino->block2->x++; mino->block2->y--;
            mino->block3->x++; mino->block3->y++;
            break;
        default:
            printf("No such rotation?");
    }
}
void rotateRightMinoI(Mino *mino) {
    switch(mino->rotation) {
        case ROT_0:
            mino->block1->x+=2; mino->block1->y--;
            mino->anchor->x++;
            mino->block2->y++;
            mino->block3->x--; mino->block3->y+=2;
            break;
        case ROT_R:
            mino->block1->x++; mino->block1->y+=2;
            mino->anchor->y++;
            mino->block2->x--;
            mino->block3->x-=2; mino->block3->y--;
            break;
        case ROT_2:
            mino->block1->x-=2; mino->block1->y++;
            mino->anchor->x--;
            mino->block2->y--;
            mino->block3->x++; mino->block3->y-=2;
            break;
        case ROT_L:
            mino->block1->x--; mino->block1->y-=2;
            mino->anchor->y--;
            mino->block2->x++;
            mino->block3->x+=2; mino->block3->y++;
            break;
        default:
            printf("No such rotation?");
    }
}

bool isRotationLegal(GameState *gameState, Settings *settings) {
    if(!isRightLegal(gameState, settings->GridWidth)) return false;
    if(!isLeftLegal(gameState)) return false;
    if(!isDownLegal(gameState, settings->GridHeight)) return false;
    return true;
}

void rotateLeft(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;
    Board *board = gameState->boards->leftBoard;

    if(mino->minoType == MinoO) return;
    if(mino->minoType == MinoI) {
        rotateLeftI(gameState, settings);
    }
    else {
        rotateLeftJLTSZ(gameState, settings);
    }
    correctMinoPos(gameState, settings->BlockSize);

    copyMinoPosition(gameState->mino, gameState->ghostMino);
    softDropGhost(gameState, settings);
}

void rotateRight(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;
    Board *board = gameState->boards->leftBoard;

    if(mino->minoType == MinoO) return;
    if(mino->minoType == MinoI) {
        rotateRightI(gameState, settings);
    }
    else {
        rotateRightJLTSZ(gameState, settings);
    }
    correctMinoPos(gameState, settings->BlockSize);

    copyMinoPosition(gameState->mino, gameState->ghostMino);
    softDropGhost(gameState, settings);
}

void rotate180(GameState *gameState, Settings *settings) {

}

void rotateLeftJLTSZ(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;
    Mino *revertMino = copyMino(mino);

    switch(mino->minoType) {
        case MinoJ: rotateLeftMinoJ(mino); break;
        case MinoL: rotateLeftMinoL(mino); break;
        case MinoT: rotateLeftMinoT(mino); break;
        case MinoS: rotateLeftMinoS(mino); break;
        case MinoZ: rotateLeftMinoZ(mino); break;
        default:
            printf("No such mino.");
    }
    bool revertRotation = false;
    switch(mino->rotation) {
        case ROT_0:
            revertRotation = leftTestsJLTSZRot0(gameState, settings);
            break;
        case ROT_R:
            revertRotation = leftTestsJLTSZRotR(gameState, settings);
            break;
        case ROT_2:
            revertRotation = leftTestsJLTSZRot2(gameState, settings);
            break;
        case ROT_L:
            revertRotation = leftTestsJLTSZRotL(gameState, settings);
            break;
        default:
            printf("No such rotation?");
    }
    if(revertRotation) {
        freeMino(mino);
        gameState->mino = revertMino;
        return;
    }
    freeMino(revertMino);
    mino->rotation--;
    if(mino->rotation == -1) mino->rotation = ROT_L;
}

void rotateLeftI(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;
    Mino *revertMino = copyMino(mino);

    rotateLeftMinoI(mino);
    bool revertRotation = false;
    switch(mino->rotation) {
        case ROT_0:
            revertRotation = leftTestsIRot0(gameState, settings);
            break;
        case ROT_R:
            revertRotation = leftTestsIRotR(gameState, settings);
            break;
        case ROT_2:
            revertRotation = leftTestsIRot2(gameState, settings);
            break;
        case ROT_L:
            revertRotation = leftTestsIRotL(gameState, settings);
            break;
        default:
            printf("No such rotation?");
    }
    if(revertRotation) {
        freeMino(mino);
        gameState->mino = revertMino;
        return;
    }
    freeMino(revertMino);
    mino->rotation--;
    if(mino->rotation == -1) mino->rotation = ROT_L;
}

void rotateRightJLTSZ(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;
    Mino *revertMino = copyMino(mino);

    switch(mino->minoType) {
        case MinoJ: rotateRightMinoJ(mino); break;
        case MinoL: rotateRightMinoL(mino); break;
        case MinoT: rotateRightMinoT(mino); break;
        case MinoS: rotateRightMinoS(mino); break;
        case MinoZ: rotateRightMinoZ(mino); break;
        default:
            printf("No such mino.");
    }
    bool revertRotation = false;
    switch(mino->rotation) {
        case ROT_0:
            revertRotation = rightTestsJLTSZRot0(gameState, settings);
            break;
        case ROT_R:
            revertRotation = rightTestsJLTSZRotR(gameState, settings);
            break;
        case ROT_2:
            revertRotation = rightTestsJLTSZRot2(gameState, settings);
            break;
        case ROT_L:
            revertRotation = rightTestsJLTSZRotL(gameState, settings);
            break;
        default:
            printf("No such rotation?");
    }
    if(revertRotation) {
        freeMino(mino);
        gameState->mino = revertMino;
        return;
    }
    freeMino(revertMino);
    mino->rotation = (mino->rotation+1) % 4;
}

void rotateRightI(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;
    Mino *revertMino = copyMino(mino);

    rotateRightMinoI(mino);
    bool revertRotation = false;
    switch(mino->rotation) {
        case ROT_0:
            revertRotation = rightTestsIRot0(gameState, settings);
            break;
        case ROT_R:
            revertRotation = rightTestsIRotR(gameState, settings);
            break;
        case ROT_2:
            revertRotation = rightTestsIRot2(gameState, settings);
            break;
        case ROT_L:
            revertRotation = rightTestsIRotL(gameState, settings);
            break;
        default:
            printf("No such rotation?");
    }
    if(revertRotation) {
        freeMino(mino);
        gameState->mino = revertMino;
        return;
    }
    freeMino(revertMino);
    mino->rotation = (mino->rotation+1) % 4;
}

bool leftTestsJLTSZRot0(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;

    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, 1); // test 2
    if(!isRotationLegal(gameState, settings)) moveMinoY(mino, -1); // test 3
    if(!isRotationLegal(gameState, settings)) { // test 4
        moveMinoX(mino, -1);
        moveMinoY(mino, 3);
    }
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, 1); // test 5
    if(!isRotationLegal(gameState, settings)) return true;
    return false;
}

bool leftTestsJLTSZRotR(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;

    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, 1); // test 2
    if(!isRotationLegal(gameState, settings)) moveMinoY(mino, 1); // test 3
    if(!isRotationLegal(gameState, settings)) { // test 4
        moveMinoX(mino, -1);
        moveMinoY(mino, -3);
    }
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, 1); // test 5
    if(!isRotationLegal(gameState, settings)) return true;
    return false;
}

bool leftTestsJLTSZRot2(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;

    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, -1); // test 2
    if(!isRotationLegal(gameState, settings)) moveMinoY(mino, -1); // test 3
    if(!isRotationLegal(gameState, settings)) { // test 4
        moveMinoX(mino, 1);
        moveMinoY(mino, 3);
    }
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, -1); // test 5
    if(!isRotationLegal(gameState, settings)) return true;
    return false;
}

bool leftTestsJLTSZRotL(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;
    
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, -1); // test 2
    if(!isRotationLegal(gameState, settings)) moveMinoY(mino, 1); // test 3
    if(!isRotationLegal(gameState, settings)) { // test 4
        moveMinoX(mino, 1);
        moveMinoY(mino, -3);
    }
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, -1); // test 5
    if(!isRotationLegal(gameState, settings)) return true;
    return false;
}

bool leftTestsIRot0(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;

    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, -1); // test 2
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, 3); // test 3
    if(!isRotationLegal(gameState, settings)) { // test 4
        moveMinoX(mino, -3);
        moveMinoY(mino, -2);
    }
    if(!isRotationLegal(gameState, settings)) { // test 5
        moveMinoX(mino, 3);
        moveMinoY(mino, 3);
    }
    if(!isRotationLegal(gameState, settings)) return true;
    return false;
}
bool leftTestsIRotR(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;


    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, 2); // test 2
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, -3); // test 3
    if(!isRotationLegal(gameState, settings)) { // test 4
        moveMinoX(mino, 3);
        moveMinoY(mino, -1);
    }
    if(!isRotationLegal(gameState, settings)) { // test 5
        moveMinoX(mino, -3);
        moveMinoY(mino, 3);
    }
    if(!isRotationLegal(gameState, settings)) return true;
    return false;
}
bool leftTestsIRot2(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;

    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, 1); // test 2
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, -3); // test 3
    if(!isRotationLegal(gameState, settings)) { // test 4
        moveMinoX(mino, 3);
        moveMinoY(mino, 2);
    }
    if(!isRotationLegal(gameState, settings)) { // test 5
        moveMinoX(mino, -3);
        moveMinoY(mino, -3);
    }
    if(!isRotationLegal(gameState, settings))return true;
    return false;
}
bool leftTestsIRotL(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;

    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, -2); // test 2
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, 3); // test 3
    if(!isRotationLegal(gameState, settings)) { // test 4
        moveMinoX(mino, -3);
        moveMinoY(mino, 1);
    }
    if(!isRotationLegal(gameState, settings)) { // test 5
        moveMinoX(mino, 3);
        moveMinoY(mino, -3);
    }
    if(!isRotationLegal(gameState, settings)) return true;
    return false;
}

bool rightTestsJLTSZRot0(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;

    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, -1); // test 2
    if(!isRotationLegal(gameState, settings)) moveMinoY(mino, -1); // test 3
    if(!isRotationLegal(gameState, settings)) { // test 4
        moveMinoX(mino, 1);
        moveMinoY(mino, 3);
    }
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, -1); // test 5
    if(!isRotationLegal(gameState, settings)) return true;
    return false;
}
bool rightTestsJLTSZRotR(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;

    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, 1); // test 2
    if(!isRotationLegal(gameState, settings)) moveMinoY(mino, 1); // test 3
    if(!isRotationLegal(gameState, settings)) { // test 4
        moveMinoX(mino, -1);
        moveMinoY(mino, -3);
    }
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, 1); // test 5
    if(!isRotationLegal(gameState, settings)) return true;
    return false;
}
bool rightTestsJLTSZRot2(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;

    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, 1); // test 2
    if(!isRotationLegal(gameState, settings)) moveMinoY(mino, -1); // test 3
    if(!isRotationLegal(gameState, settings)) { // test 4
        moveMinoX(mino, -1);
        moveMinoY(mino, 3);
    }
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, 1); // test 5
    if(!isRotationLegal(gameState, settings)) return true;
    return false;
}
bool rightTestsJLTSZRotL(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;

    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, -1); // test 2
    if(!isRotationLegal(gameState, settings)) moveMinoY(mino, 1); // test 3
    if(!isRotationLegal(gameState, settings)) { // test 4
        moveMinoX(mino, 1);
        moveMinoY(mino, -3);
    }
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, -1); // test 5
    if(!isRotationLegal(gameState, settings)) return true;
    return false;
}

bool rightTestsIRot0(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;

    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, -2); // test 2
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, 3); // test 3
    if(!isRotationLegal(gameState, settings)) { // test 4
        moveMinoX(mino, -3);
        moveMinoY(mino, 1);
    }
    if(!isRotationLegal(gameState, settings)) { // test 5
        moveMinoX(mino, 3);
        moveMinoY(mino, -3);
    }
    if(!isRotationLegal(gameState, settings)) return true;
    return false;
}
bool rightTestsIRotR(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;

    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, -1); // test 2
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, 3); // test 3
    if(!isRotationLegal(gameState, settings)) { // test 4
        moveMinoX(mino, -3);
        moveMinoY(mino, -2);
    }
    if(!isRotationLegal(gameState, settings)) { // test 5
        moveMinoX(mino, 3);
        moveMinoY(mino, 3);
    }
    if(!isRotationLegal(gameState, settings)) return true;
    return false;
}
bool rightTestsIRot2(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;

    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, 2); // test 2
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, -3); // test 3
    if(!isRotationLegal(gameState, settings)) { // test 4
        moveMinoX(mino, 3);
        moveMinoY(mino, -1);
    }
    if(!isRotationLegal(gameState, settings)) { // test 5
        moveMinoX(mino, -3);
        moveMinoY(mino, 3);
    }
    if(!isRotationLegal(gameState, settings)) return true;
    return false;
}
bool rightTestsIRotL(GameState *gameState, Settings *settings) {
    Mino *mino = gameState->mino;

    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, 1); // test 2
    if(!isRotationLegal(gameState, settings)) moveMinoX(mino, -3); // test 3
    if(!isRotationLegal(gameState, settings)) { // test 4
        moveMinoX(mino, 3);
        moveMinoY(mino, 2);
    }
    if(!isRotationLegal(gameState, settings)) { // test 5
        moveMinoX(mino, -3);
        moveMinoY(mino, -3);
    }
    if(!isRotationLegal(gameState, settings)) return true;
    return false;
}