#ifndef LINESENDS_H
#define LINESENDS_H

#include "gameState.h"

void recieveLines(GameState *gameState);
void recieveLine(GameState *gameState, int ignoredColumn);

int lineSendCalculation(GameState *gameState);

#endif