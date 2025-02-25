#include "snakeXP.h"
#include "raylib.h"
#include "gameObjects.h"


void gameLoop(const Color background, const Color drawColor, const int cellSize, const int cellCount) {
    Food food = Food(cellSize, drawColor, 5, 6);

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(background);

        food.draw();

        EndDrawing();
    }
    CloseWindow();
}