#ifndef PREVIEWANDHOLD_H
#define PREVIEWANDHOLD_H

#include "raylib.h"
#include "minos.h"

typedef struct Preview {
    Rectangle rect;
    MinoType minoType;
} Preview;

typedef struct PreviewColumn {
    int size;
    int startX;
    int startY;
    Preview *previews;
} PreviewCol;

PreviewCol *createPreviewCol(Settings *settings);
PreviewCol *createRightPreviewCol(Settings *settings);
Preview createPreview(Settings *settings, int i);
Preview createRightPreview(Settings *settings, int i);
void freePreviewCol(PreviewCol *previewCol);

Preview *getPreview(PreviewCol *previewCol, int i);

void drawPreviewCol(PreviewCol *previewCol, Settings *settings);
void drawPreview(Settings *settings, Preview *preview);
void drawRightPreviewCol(PreviewCol *previewCol, Settings *settings);
void drawRightPreview(Settings *settings, Preview *preview);

void updatePreviewCol(PreviewCol *previewCol, Bags *bags);
PreviewCol *copyPreviewCol(PreviewCol *previewCol);

#endif