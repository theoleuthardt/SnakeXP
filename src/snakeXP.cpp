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

void SetupGame(const int cellSize, const int cellCount) {
    // initial game configuration
    InitWindow(cellSize * cellCount, cellSize * cellCount, "SnakeXP");
    SetTargetFPS(60);

    // game icon
    const Image icon = LoadImage("assets/icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
}

void DrawMainMenu(const Color background, const Color drawColor, const int cellSize, const int cellCount) {
    while (WindowShouldClose() == false && IsKeyPressed(KEY_ENTER) == false) {
        BeginDrawing();
        ClearBackground(background);

        DrawText("SnakeXP", cellSize * cellCount / 2 - 200, cellSize * cellCount / 2 - 200, 100, drawColor);
        DrawText("Press [ENTER] to Start", cellSize * cellCount / 2 - 200, cellSize * cellCount / 2, 30, drawColor);
        DrawText("Press [ESC] to Exit", cellSize * cellCount / 2 - 200, cellSize * cellCount / 2 + 50, 30, drawColor);

        EndDrawing();
    }
}

void GameLoop(const Color background, const Color drawColor, const int cellSize, const int cellCount) {
    Food food = Food(cellSize, cellCount, drawColor);
    cout << "Food position: " << food.position.x << ", " << food.position.y << endl;

    while (WindowShouldClose() == false && IsKeyPressed(KEY_ESCAPE) == false) {
        BeginDrawing();
        ClearBackground(background);

        DrawGrid(cellSize, cellCount, drawColor);
        food.Draw();

        EndDrawing();
    }
    CloseWindow();
}