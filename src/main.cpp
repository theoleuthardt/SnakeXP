#include "raylib.h"
#include "snakeXP.h"
#include "gameStates.h"

void UpdateScalingFactors(int cellSize, int cellCount, int borderSize, int scoreHeight, float& scale,
                          float& scaleX, float& scaleY, int& baseWidth, int& baseHeight);

int main() {
    // window & styling configuration
    constexpr Color background = {0, 0, 0, 255};
    constexpr Color drawColor = {255, 255, 255, 255};
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
                DrawMainMenu(background, drawColor, scale, scaleX, scaleY);
                // check for user input
                if (IsKeyPressed(KEY_ENTER)) {
                    gameState = GAMEPLAY;
                } else if (IsKeyPressed(KEY_ESCAPE)) {
                    gameState = EXIT;
                }
                break;

            case GAMEPLAY:
                GameLoop(background, drawColor, cellSize, cellCount, borderSize, scoreHeight, scale, scaleX, scaleY);
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

void UpdateScalingFactors(const int cellSize, const int cellCount, const int borderSize, const int scoreHeight,
                              float&scale, float&scaleX, float&scaleY, int&baseWidth, int&baseHeight) {
    baseWidth = cellSize * cellCount + 2 * borderSize;
    baseHeight = cellSize * cellCount + 2 * borderSize + scoreHeight;

    scaleX = static_cast<float>(GetScreenWidth()) / baseWidth;
    scaleY = static_cast<float>(GetScreenHeight()) / baseHeight;

    scale = scaleX < scaleY ? scaleX : scaleY;
}