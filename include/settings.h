#ifndef SETTINGS_H
#define SETTINGS_H

#include <string.h>
#include "raylib.h"

typedef struct Settings {
    int StartX;
    int StartY;
    int OpponentStartX;
    int ScreenWidth;
    int ScreenHeight;
    int FrameRate;
    int GridWidth;
    int GridHeight;
    int PreviewMinoCount;
    float OutlineThickness;
    float BoardlineThickness;
    int BlockSize;
    Color BoardColor;
    Color OutlineColor;
    Color BoardEdgeColor;
    Color GarbageColor;
    float GhostMinoAlpha;
    float Das;
    int HardDrop;
    int SoftDrop;
    int MoveLeft;
    int MoveRight;
    int RotateLeft;
    int RotateRight;
    int Rotate180;
    int Hold;
}Settings;

Settings *createSettingsStruct();
void loadSettings(Settings *settings, const char *filename);
void saveSettings(Settings *settings, const char *filename);
void setDefaultSettings(Settings *settings);
void printSettings(Settings *settings);
void freeSettings(Settings *settings);

void editHardDropBind(Settings *settings, int binding);

#endif