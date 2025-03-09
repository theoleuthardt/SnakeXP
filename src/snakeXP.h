#ifndef SNAKEXP_H
#define SNAKEXP_H
#include "raylib.h"
#include <iostream>

using namespace std;

int ScaledX(float scaleX, int x);

int ScaledY(float scaleY, int y);

int ScaledSize(int size, int value);

void SetupGame(int cellSize, int cellCount, int borderSize, int scoreHeight);

void DrawMainMenu(Color background, Color drawColor, float scale, float scaleX, float scaleY);

void GameLoop(Color background, Color drawColor, int cellSize, int cellCount, int borderSize, int scoreHeight,
    float scale, float scaleX, float scaleY);

#endif