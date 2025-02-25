#include "snakeXP.h"
#include "raylib.h"
#include "gameObjects.h"
#include <iostream>

using namespace std;

void gameLoop(const Color background, const Color drawColor, const int cellSize, const int cellCount) {
    Food food = Food(cellSize, drawColor, 5, 6);
    food.randomizePosition(cellCount);
    cout << "Food position: " << food.position.x << ", " << food.position.y << endl;

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(background);
        food.draw();

        EndDrawing();
    }
    CloseWindow();
}