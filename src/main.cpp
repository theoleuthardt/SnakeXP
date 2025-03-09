#include "raylib.h"
#include "snakeXP.h"
#include "gameStates.h"
#include "scaling.h"

int main() {
    // window & styling configuration
    constexpr float backgroundSpeed = 0.5f;
    constexpr int cellSize = 40;
    constexpr int cellCount = 20;
    constexpr int borderSize = 40;
    constexpr int scoreHeight = 60;
    float scale = 1.0f;
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    int baseWidth;
    int baseHeight;

    // game values
    int score = 0;
    int highScore = 0;
    int level = 1;

    SetupGame(cellSize, cellCount, borderSize, scoreHeight);
    GameState gameState = MAIN_MENU;
    bool exitRequested = false;

    while (!exitRequested) {
        BeginDrawing();

        UpdateScalingFactors(cellSize, cellCount, borderSize, scoreHeight, scale, scaleX, scaleY, baseWidth,
            baseHeight);
        if (WindowShouldClose()) {
            exitRequested = true;
        }

        switch (gameState) {
            case MAIN_MENU:
                DrawMainMenu(backgroundSpeed, scale);
                // check for user input
                if (IsKeyPressed(KEY_ENTER)) {
                    gameState = GAMEPLAY;
                } else if (IsKeyPressed(KEY_ESCAPE)) {
                    gameState = EXIT;
                }
                break;

            case GAMEPLAY:
                GameLoop(cellSize, cellCount, borderSize, scoreHeight, scale);
                // check for user input
                if (IsKeyPressed(KEY_ESCAPE)) {
                    gameState = MAIN_MENU;
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