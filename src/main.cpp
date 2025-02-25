#include "raylib.h"
#include "snakeXP.h"
#include "gameStates.h"

int main() {
    constexpr Color background = {9, 20, 227, 255};
    constexpr Color drawColor = {255, 255, 255, 255};
    constexpr int cellSize = 60;
    constexpr int cellCount = 20;

    SetupGame(cellSize, cellCount);
    GameState gameState = MAIN_MENU;

    while (gameState != EXIT) {
        BeginDrawing();

        switch (gameState) {
            case MAIN_MENU:
                DrawMainMenu(background, drawColor, cellSize, cellCount);
                if (IsKeyPressed(KEY_ENTER)) {
                    gameState = GAMEPLAY;
                } else if (IsKeyPressed(KEY_ESCAPE)) {
                    gameState = EXIT;
                }
                break;

            case GAMEPLAY:
                GameLoop(background, drawColor, cellSize, cellCount);
                if (WindowShouldClose()) {
                    gameState = EXIT;
                }
                break;

            case EXIT:
                break;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
