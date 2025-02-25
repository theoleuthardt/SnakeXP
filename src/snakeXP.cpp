#include "snakeXP.h"
#include "raylib.h"
#include "gameObjects.h"
#include <iostream>

using namespace std;

void DrawGrid(const int cellSize, const int cellCount, const Color color) {
    for (int i = 0; i <= cellCount; i++) {
        DrawLine(i * cellSize, 0, i * cellSize, cellSize * cellCount, color);
        DrawLine(0, i * cellSize, cellSize * cellCount, i * cellSize, color);
    }
}

void GameLoop(const Color background, const Color drawColor, const int cellSize, const int cellCount) {
    Food food = Food(cellSize, cellCount, drawColor);
    cout << "Food position: " << food.position.x << ", " << food.position.y << endl;

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(background);

        DrawGrid(cellSize, cellCount, drawColor);
        food.Draw();

        EndDrawing();
    }
    CloseWindow();
}