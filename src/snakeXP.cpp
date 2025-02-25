#include "snakeXP.h"
#include "raylib.h"
#include "gameObjects.h"
#include <iostream>

using namespace std;

void drawGrid(const int cellSize, const int cellCount, const Color color) {
    for (int i = 0; i <= cellCount; i++) {
        DrawLine(i * cellSize, 0, i * cellSize, cellSize * cellCount, color);
        DrawLine(0, i * cellSize, cellSize * cellCount, i * cellSize, color);
    }
}

void gameLoop(const Color background, const Color drawColor, const int cellSize, const int cellCount) {
    Food food = Food(cellSize, drawColor, 5, 6);
    food.randomizePosition(cellCount);
    cout << "Food position: " << food.position.x << ", " << food.position.y << endl;

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(background);
        drawGrid(cellSize, cellCount, drawColor);
        food.draw();

        EndDrawing();
    }
    CloseWindow();
}