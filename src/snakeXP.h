#ifndef SNAKEXP_H
#define SNAKEXP_H
#include "raylib.h"

void SetupGame(int cellSize, int cellCount);

void DrawMainMenu(Color background, Color drawColor, int cellSize, int cellCount);

void GameLoop(Color background, Color drawColor, int cellSize, int cellCount);

#endif