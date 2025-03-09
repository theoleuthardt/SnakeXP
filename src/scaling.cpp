#include "scaling.h"
#include "raylib.h"

void UpdateScalingFactors(const int cellSize, int cellCount, const int borderSize, const int scoreHeight,
                          float &scale, float &scaleX, float &scaleY, int &baseWidth, int &baseHeight) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // ensure square window
    int updatedSize = (screenWidth < screenHeight) ? screenWidth : screenHeight;
    if (screenWidth != screenHeight) {
        SetWindowSize(updatedSize, updatedSize);
    }

    // calculate scale factors
    int availableSpace = updatedSize - (2 * borderSize) - scoreHeight;
    constexpr int minCellSize = 16;
    int maxCellCount = availableSpace / minCellSize;
    if (maxCellCount < cellCount) {
        cellCount = maxCellCount > 8 ? maxCellCount : 8;
    }

    baseWidth = cellSize * cellCount + 2 * borderSize;
    baseHeight = cellSize * cellCount + 2 * borderSize + scoreHeight;

    scaleX = static_cast<float>(updatedSize) / baseWidth;
    scaleY = static_cast<float>(updatedSize) / baseHeight;
    scale = scaleX < scaleY ? scaleX : scaleY;

    // ensure minimum scale
    if (cellSize * scale < 8) {
        scale = 8.0f / cellSize;
    }

}

