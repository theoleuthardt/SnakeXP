#include "gameSetup.h"
#include "raylib.h"
#include <iostream>

using namespace std;

void SetupGame(const int cellSize, const int cellCount) {
    // initial game configuration
    InitWindow(cellSize * cellCount, cellSize * cellCount, "SnakeXP");
    SetTargetFPS(60);

    // game icon
    const Image icon = LoadImage("assets/icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
}