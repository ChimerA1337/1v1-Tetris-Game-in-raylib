#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "../include/settings.h"
#include "../include/definitions.h"

typedef struct Settings Settings;

Settings *createSettingsStruct() {
    Settings *settings = malloc(sizeof(Settings));
    return settings;
}

void freeSettings(Settings *settings) {
    free(settings);
}

void loadSettings(Settings *settings, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        setDefaultSettings(settings);
        return;
    }
    
    char key[64];
    float value;

    while(fscanf(file, "%63[^=]=%f\n", key, &value) == 2) {
        if(strcmp(key, "StartX") == 0) settings->StartX = (int)value;
        else if(strcmp(key, "StartY") == 0) settings->StartY = (int)value;
        else if(strcmp(key, "OpponentStartX") == 0) settings->OpponentStartX = (int)value;
        else if(strcmp(key, "ScreenWidth") == 0) settings->ScreenWidth = (int)value;
        else if(strcmp(key, "ScreenHeight") == 0) settings->ScreenHeight = (int)value;
        else if(strcmp(key, "FrameRate") == 0) settings->FrameRate = (int)value;
        else if(strcmp(key, "GridWidth") == 0) settings->GridWidth = (int)value;
        else if(strcmp(key, "GridHeight") == 0) settings->GridHeight = (int)value;
        else if(strcmp(key, "PreviewMinoCount") == 0) settings->PreviewMinoCount = (int)value;
        else if(strcmp(key, "BoardOutlineThickness") == 0) settings->OutlineThickness = value;
        else if(strcmp(key, "BoardlineThickness") == 0) settings->BoardlineThickness = value;
        else if(strcmp(key, "BlockSize") == 0) settings->BlockSize = (int)value;
        else if(strcmp(key, "BoardColorR") == 0) settings->BoardColor.r = (int)value;
        else if(strcmp(key, "BoardColorG") == 0) settings->BoardColor.g = (int)value;
        else if(strcmp(key, "BoardColorB") == 0) settings->BoardColor.b = (int)value;
        else if(strcmp(key, "BoardColorA") == 0) settings->BoardColor.a = (int)value;
        else if(strcmp(key, "OutlineColorR") == 0) settings->OutlineColor.r = (int)value;
        else if(strcmp(key, "OutlineColorG") == 0) settings->OutlineColor.g = (int)value;
        else if(strcmp(key, "OutlineColorB") == 0) settings->OutlineColor.b = (int)value;
        else if(strcmp(key, "OutlineColorA") == 0) settings->OutlineColor.a = (int)value;
        else if(strcmp(key, "BoardEdgeColorR") == 0) settings->BoardEdgeColor.r = (int)value;
        else if(strcmp(key, "BoardEdgeColorG") == 0) settings->BoardEdgeColor.g = (int)value;
        else if(strcmp(key, "BoardEdgeColorB") == 0) settings->BoardEdgeColor.b = (int)value;
        else if(strcmp(key, "BoardEdgeColorA") == 0) settings->BoardEdgeColor.a = (int)value;
        else if(strcmp(key, "GarbageColorR") == 0) settings->GarbageColor.r = (int)value;
        else if(strcmp(key, "GarbageColorG") == 0) settings->GarbageColor.g = (int)value;
        else if(strcmp(key, "GarbageColorB") == 0) settings->GarbageColor.b = (int)value;
        else if(strcmp(key, "GarbageColorA") == 0) settings->GarbageColor.a = (int)value;
        else if(strcmp(key, "GhostMinoAlpha") == 0) settings->GhostMinoAlpha = value;
        else if(strcmp(key, "Das") == 0) settings->Das = value;
        else if(strcmp(key, "HardDrop") == 0) settings->HardDrop = (int)value;
        else if(strcmp(key, "SoftDrop") == 0) settings->SoftDrop = (int)value;
        else if(strcmp(key, "MoveLeft") == 0) settings->MoveLeft = (int)value;
        else if(strcmp(key, "MoveRight") == 0) settings->MoveRight = (int)value;
        else if(strcmp(key, "RotateLeft") == 0) settings->RotateLeft = (int)value;
        else if(strcmp(key, "RotateRight") == 0) settings->RotateRight = (int)value;
        else if(strcmp(key, "Rotate180") == 0) settings->Rotate180 = (int)value;
        else if(strcmp(key, "Hold") == 0) settings->Hold = (int)value;
    }
    fclose(file);

    printf("\nSettings loaded from %s\n", filename);
    //printSettings(settings);
}
void saveSettings(Settings *settings, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Failed to open settings file for writing: %s\n", filename);
        return;
    }

    fprintf(file, "StartX=%d\n", settings->StartX);
    fprintf(file, "StartY=%d\n", settings->StartY);
    fprintf(file, "OpponentStartX=%d\n", settings->OpponentStartX);
    fprintf(file, "ScreenWidth=%d\n", settings->ScreenWidth);
    fprintf(file, "ScreenHeight=%d\n", settings->ScreenHeight);
    fprintf(file, "FrameRate=%d\n", settings->FrameRate);
    fprintf(file, "GridWidth=%d\n", settings->GridWidth);
    fprintf(file, "GridHeight=%d\n", settings->GridHeight);
    fprintf(file, "PreviewMinoCount=%d\n", settings->PreviewMinoCount);
    fprintf(file, "BoardOutlineThickness=%.2f\n", settings->OutlineThickness);
    fprintf(file, "BoardlineThickness=%.2f\n", settings->BoardlineThickness);
    fprintf(file, "BlockSize=%d\n", settings->BlockSize);
    fprintf(file, "BoardColorR=%d\n", settings->BoardColor.r);
    fprintf(file, "BoardColorG=%d\n", settings->BoardColor.g);
    fprintf(file, "BoardColorB=%d\n", settings->BoardColor.b);
    fprintf(file, "BoardColorA=%d\n", settings->BoardColor.a);
    fprintf(file, "OutlineColorR=%d\n", settings->OutlineColor.r);
    fprintf(file, "OutlineColorG=%d\n", settings->OutlineColor.g);
    fprintf(file, "OutlineColorB=%d\n", settings->OutlineColor.b);
    fprintf(file, "OutlineColorA=%d\n", settings->OutlineColor.a);
    fprintf(file, "BoardEdgeColorR=%d\n", settings->BoardEdgeColor.r);
    fprintf(file, "BoardEdgeColorG=%d\n", settings->BoardEdgeColor.g);
    fprintf(file, "BoardEdgeColorB=%d\n", settings->BoardEdgeColor.b);
    fprintf(file, "BoardEdgeColorA=%d\n", settings->BoardEdgeColor.a);
    fprintf(file, "GarbageColorR=%d\n", settings->BoardEdgeColor.r);
    fprintf(file, "GarbageColorG=%d\n", settings->BoardEdgeColor.g);
    fprintf(file, "GarbageColorB=%d\n", settings->BoardEdgeColor.b);
    fprintf(file, "GarbageColorA=%d\n", settings->BoardEdgeColor.a);
    fprintf(file, "GhostMinoAlpha=%.2f\n", settings->GhostMinoAlpha);
    fprintf(file, "Das=%.4f\n", settings->Das);
    fprintf(file, "HardDrop=%d\n", settings->HardDrop);
    fprintf(file, "SoftDrop=%d\n", settings->SoftDrop);
    fprintf(file, "MoveLeft=%d\n", settings->MoveLeft);
    fprintf(file, "MoveRight=%d\n", settings->MoveRight);
    fprintf(file, "RotateLeft=%d\n", settings->RotateLeft);
    fprintf(file, "RotateRight=%d\n", settings->RotateRight);
    fprintf(file, "Rotate180=%d\n", settings->Rotate180);
    fprintf(file, "Hold=%d\n", settings->Hold);

    fclose(file);
}

void setDefaultSettings(Settings *settings) {
    settings->StartX = 100;
    settings->StartY = 100;
    settings->OpponentStartX = 1069;
    settings->ScreenWidth = SCREEN_WIDTH;
    settings->ScreenHeight = SCREEN_HEIGHT;
    settings->FrameRate = FRAME_RATE;
    settings->GridWidth = GRID_WIDTH;
    settings->GridHeight = GRID_HEIGHT;
    settings->PreviewMinoCount = PREVIEW_PIECE_COUNT;
    settings->OutlineThickness = OUTLINE_THICKNESS;
    settings->BoardlineThickness = BOARD_OUTLINE_THICKNESS;
    settings->BlockSize = BLOCKSIZE;
    settings->BoardColor = DARKGRAY;
    settings->OutlineColor = GRAY;
    settings->BoardEdgeColor = WHITE;
    settings->GarbageColor = (Color) {220, 220, 220, 255};
    settings->GhostMinoAlpha = 0.5;
    settings->Das = 0.16;
    settings->HardDrop = KEY_SPACE;
    settings->SoftDrop = KEY_DOWN;
    settings->MoveLeft = KEY_LEFT;
    settings->MoveRight = KEY_RIGHT;
    settings->RotateLeft = KEY_Z;
    settings->RotateRight = KEY_X;
    settings->Rotate180 = KEY_V;
    settings->Hold = KEY_C;
}

void printSettings(Settings *settings) {
    printf("StartX: %d\n", settings->StartX);
    printf("StartY: %d\n", settings->StartY);
    printf("OpponentStartX: %d\n", settings->OpponentStartX);
    printf("ScreenWidth: %d\n", settings->ScreenWidth);
    printf("ScreenHeight: %d\n", settings->ScreenHeight);
    printf("FrameRate: %d\n", settings->FrameRate);
    printf("GridWidth: %d\n", settings->GridWidth);
    printf("GridHeight: %d\n", settings->GridHeight);
    printf("PreviewMinoCount: %d\n", settings->PreviewMinoCount);
    printf("OutlineThickness: %.2f\n", settings->OutlineThickness);
    printf("BoardlineThickness: %.2f\n", settings->BoardlineThickness);
    printf("BlockSize: %d\n", settings->BlockSize);
    printf("BoardColor100: (%d, %d, %d, %d)\n", settings->BoardColor.r, settings->BoardColor.g, settings->BoardColor.b, settings->BoardColor.a);
    printf("OutlineColor: (%d, %d, %d, %d)\n", settings->OutlineColor.r, settings->OutlineColor.g, settings->OutlineColor.b, settings->OutlineColor.a);
    printf("BoardEdgeColor: (%d, %d, %d, %d)\n", settings->BoardEdgeColor.r, settings->BoardEdgeColor.g, settings->BoardEdgeColor.b, settings->BoardEdgeColor.a);
    printf("GarbageColor: (%d, %d, %d, %d)\n", settings->GarbageColor.r, settings->GarbageColor.g, settings->GarbageColor.b, settings->GarbageColor.a);
    printf("GhostMinoAlpha: %.2f\n", settings->GhostMinoAlpha);
    printf("Das: %.2f\n", settings->Das);
    printf("HardDrop: %d\n", settings->HardDrop);
    printf("SoftDrop: %d\n", settings->SoftDrop);
    printf("MoveLeft: %d\n", settings->MoveLeft);
    printf("MoveRight: %d\n", settings->MoveRight);
    printf("RotateLeft: %d\n", settings->RotateLeft);
    printf("RotateRight: %d\n", settings->RotateRight);
    printf("Rotate180: %d\n", settings->Rotate180);
    printf("Hold: %d\n", settings->Hold);
}