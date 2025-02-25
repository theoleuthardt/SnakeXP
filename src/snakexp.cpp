#include "snakexp.h"
#include "raylib.h"


void gameLoop() {
    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Welcome to the Snake Game!", 100, 100, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
}