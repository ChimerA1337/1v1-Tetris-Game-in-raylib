#include "../include/preview.h"
#include <stdlib.h>
//#include <stdio.h>
#include "../include/settings.h"
#include "../include/randomizer.h"

static int MINO_SHAPES[7][4][2] = {
    [MinoI] = {{-1,0},{0,0},{1,0},{2,0}},
    [MinoO] = {{0,0},{1,0},{0,1},{1,1}},
    [MinoT] = {{-1,0},{0,0},{1,0},{0,-1}},
    [MinoL] = {{-1,0},{0,0},{1,0},{1,-1}},
    [MinoJ] = {{-1,-1},{-1,0},{0,0},{1,0}},
    [MinoS] = {{-1,0},{0,0},{0,-1},{1,-1}},
    [MinoZ] = {{-1,-1},{0,-1},{0,0},{1,0}}
};

PreviewCol *createPreviewCol(Settings *settings) {
    Preview *previews = malloc(sizeof(Preview) * settings->PreviewMinoCount);

    PreviewCol *previewCol = malloc(sizeof(PreviewCol));
    previewCol->size = settings->PreviewMinoCount;
    previewCol->startX = settings->GridWidth * settings->BlockSize + 2 * settings->OutlineThickness;
    previewCol->startY = settings->StartY;
    previewCol->previews = previews;

    Preview *preview;
    for(int i = 0; i < previewCol->size; i++) {
        preview = getPreview(previewCol, i);
        *preview = createPreview(settings, i);
    }
    return previewCol;
}

PreviewCol *createRightPreviewCol(Settings *settings) {
    Preview *previews = malloc(sizeof(Preview) * settings->PreviewMinoCount);

    PreviewCol *previewCol = malloc(sizeof(PreviewCol));
    previewCol->size = settings->PreviewMinoCount;
    previewCol->startX = settings->GridWidth * settings->BlockSize + 2 * settings->OutlineThickness + 800;
    previewCol->startY = settings->StartY;
    previewCol->previews = previews;

    Preview *preview;
    for(int i = 0; i < previewCol->size; i++) {
        preview = getPreview(previewCol, i);
        *preview = createRightPreview(settings, i);
    }
    return previewCol;
}

Preview createPreview(Settings *settings, int i) {
    Preview preview;
    int blockSize = settings->BlockSize;
    float outline = settings->OutlineThickness;

    preview.rect.x = settings->StartX + settings->GridWidth * blockSize + outline;
    preview.rect.y = settings->StartY - 2*outline + (3*blockSize - outline) * i;
    preview.rect.width = 3*blockSize;
    preview.rect.height = 3*blockSize;

    return preview;
}

Preview createRightPreview(Settings *settings, int i) {
    Preview preview;
    int blockSize = settings->BlockSize;
    float outline = settings->OutlineThickness;

    preview.rect.x = settings->StartX + settings->GridWidth * blockSize + outline + 800;
    preview.rect.y = settings->StartY - 2*outline + (3*blockSize - outline) * i;
    preview.rect.width = 3*blockSize;
    preview.rect.height = 3*blockSize;

    return preview;
}

void freePreviewCol(PreviewCol *previewCol) {
    free(previewCol->previews);
    free(previewCol);
}


Preview *getPreview(PreviewCol *previewCol, int i) {
    return &previewCol->previews[i];
}

void drawPreviewCol(PreviewCol *previewCol, Settings *settings) {
    for(int i = 0; i < previewCol->size; i++) {
        drawPreview(settings, getPreview(previewCol, i));
    }
}

void drawPreview(Settings *settings, Preview *preview) {
    DrawRectangleLinesEx(preview->rect, settings->OutlineThickness, settings->BoardEdgeColor);

    int previewBlockSize = settings->BlockSize / 2;
    Color color = getMinoColor(preview->minoType);

    int centerX = preview->rect.x + preview->rect.width / 2;
    int centerY = preview->rect.y + preview->rect.height / 2;

    for (int i = 0; i < 4; i++) {
        int ox = MINO_SHAPES[preview->minoType][i][0];
        int oy = MINO_SHAPES[preview->minoType][i][1];

        Rectangle cell = {
            centerX + ox * previewBlockSize - previewBlockSize / 2,
            centerY + oy * previewBlockSize - previewBlockSize / 2,
            previewBlockSize,
            previewBlockSize
        };
        DrawRectangleRec(cell, color);
        DrawRectangleLinesEx(cell, settings->OutlineThickness, settings->BoardEdgeColor);
    }
}

void drawRightPreviewCol(PreviewCol *previewCol, Settings *settings) {
    for(int i = 0; i < previewCol->size; i++) {
        drawRightPreview(settings, getPreview(previewCol, i));
    }
}

void drawRightPreview(Settings *settings, Preview *preview) {
    Rectangle rect = preview->rect;
    rect.x += 800;

    DrawRectangleLinesEx(rect, settings->OutlineThickness, settings->BoardEdgeColor);

    int previewBlockSize = settings->BlockSize / 2;
    Color color = getMinoColor(preview->minoType);

    int centerX = preview->rect.x+800 + preview->rect.width / 2;
    int centerY = preview->rect.y + preview->rect.height / 2;

    for (int i = 0; i < 4; i++) {
        int ox = MINO_SHAPES[preview->minoType][i][0];
        int oy = MINO_SHAPES[preview->minoType][i][1];

        Rectangle cell = {
            centerX + ox * previewBlockSize - previewBlockSize / 2,
            centerY + oy * previewBlockSize - previewBlockSize / 2,
            previewBlockSize,
            previewBlockSize
        };
        DrawRectangleRec(cell, color);
        DrawRectangleLinesEx(cell, settings->OutlineThickness, settings->BoardEdgeColor);
    }
}

void updatePreviewCol(PreviewCol *previewCol, Bags *bags) {
    for (int i = 0; i < previewCol->size+1; i++) {
        Preview *preview = getPreview(previewCol, i);
        preview->minoType = (MinoType)peekBag(bags, i);
    }
}

PreviewCol *copyPreviewCol(PreviewCol *previewCol) {
    PreviewCol *copiedCol = malloc(sizeof(PreviewCol));
    copiedCol->size = previewCol->size;
    copiedCol->startX = previewCol->startX;
    copiedCol->startY = previewCol->startY;
    copiedCol->previews = malloc(sizeof(Preview) * previewCol->size);

    for(int i = 0; i < previewCol->size; i++) {
        copiedCol->previews[i] = previewCol->previews[i];
    }
    return copiedCol;
}