#include "snakeXP.h"
#include "raylib.h"
#include "gameObjects/map.h"
#include <iostream>

using namespace std;

int ScaledX(const float scaleX, const int x) {
    return x * scaleX;
}

int ScaledY(const float scaleY, const int y) {
    return y * scaleY;
}

int ScaledSize(const int size, const int value) {
    return size * value;
}

vector<Vector2> GetSnakePositions() {
    return {};
}

size_t GetScore() {
    const vector<Vector2> snakePositions = GetSnakePositions();
    return snakePositions.size() > 3 ? (snakePositions.size() - 3) * 10 : 0;
}

void DrawGame(const Color& backgroundColor, const int cellSize, const int cellCount, const int borderSize,
    const int scoreHeight, const float scale, const float scaleX, const float scaleY) {
    static SnakeTextureGrid textureGrid(cellSize, cellCount);
    static bool texturesLoaded = false;

    // calculate scaled values
    const int scaledCellSize = cellSize * scale;
    const int scaledBorderSize = borderSize * scale;
    const int scaledScoreHeight = scoreHeight * scale;

    // calculate offsets to center the game area
    int offsetX = (GetScreenWidth() - scaledCellSize * cellCount) / 2;
    int offsetY = scaledBorderSize + scaledScoreHeight;

    if (!texturesLoaded) {
        texturesLoaded = textureGrid.loadTextures("assets");
        if (!texturesLoaded) {
            DrawText("Error loading textures!", offsetX + 200 * scale, offsetY + 200 * scale, 20 * scale, RED);
            return;
        }
    }

    ClearBackground(RAYWHITE);

    const int scaledGameAreaWidth = scaledCellSize * cellCount;
    const int scaledGameAreaHeight = scaledCellSize * cellCount;
    DrawRectangle(offsetX, offsetY, scaledGameAreaWidth, scaledGameAreaHeight, backgroundColor);

    DrawRectangle(offsetX, scaledBorderSize, scaledGameAreaWidth, scaledScoreHeight - 10 * scale, LIGHTGRAY);

    const size_t score = GetScore();
    DrawText(TextFormat("SCORE: %d", score), offsetX + 20 * scale, scaledBorderSize + 10 * scale,
        30 * scale, DARKGRAY);

    for (int x = 0; x < cellCount; x++) {
        for (int y = 0; y < cellCount; y++) {
            if (y == 0) {
                textureGrid.drawTextureAt(BRICK_UP, x, y, offsetX, offsetY, scale);
            }
            else if (y == cellCount - 1) {
                textureGrid.drawTextureAt(BRICK_DOWN, x, y, offsetX, offsetY, scale);
            }
            else if (x == 0) {
                textureGrid.drawTextureAt(BRICK_LEFT, x, y, offsetX, offsetY, scale);
            }
            else if (x == cellCount - 1) {
                textureGrid.drawTextureAt(BRICK_RIGHT, x, y, offsetX, offsetY, scale);
            }
            else {
                textureGrid.drawTextureAt(EMPTY, x, y, offsetX, offsetY, scale);
            }
        }
    }

    const vector<Vector2> snakePositions = GetSnakePositions();

    for (size_t i = 0; i < snakePositions.size(); i++) {
        TextureType type;

        if (i == 0) {
            const Vector2 next = snakePositions[i + 1];
            type = SnakeTextureGrid::getSnakePartTexture(snakePositions[i], next, {}, true, false);
        }
        else if (i == snakePositions.size() - 1) {
            const Vector2 prev = snakePositions[i - 1];
            type = SnakeTextureGrid::getSnakePartTexture(snakePositions[i], prev, {}, false, true);
        }
        else {
            const Vector2 prev = snakePositions[i - 1];
            const Vector2 next = snakePositions[i + 1];
            type = SnakeTextureGrid::getSnakePartTexture(snakePositions[i], prev, next, false, false);
        }

        textureGrid.drawTextureAt(type, static_cast<int>(snakePositions[i].x),
            static_cast<int>(snakePositions[i].y), offsetX, offsetY, scale);
    }
}

void SetupGame(const int cellSize, const int cellCount, const int borderSize, const int scoreHeight) {
    // window configuration
    const int screenWidth = cellSize * cellCount + 2 * borderSize;
    const int screenHeight = cellSize * cellCount + 2 * borderSize + scoreHeight;

    // raylib initialization
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "SnakeXP");
    SetTargetFPS(60);
    SetWindowMinSize(400, 400);

    // game icon
    const Image icon = LoadImage("assets/icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
}

void DrawMainMenu(const Color background, const Color drawColor, const float scale, const float scaleX, const float scaleY) {
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const int centerX = screenWidth / 2;
    const int centerY = screenHeight / 2;

    // calculate scaled values
    const int titleFontSize = static_cast<int>(100 * scale);
    const int menuFontSize = static_cast<int>(30 * scale);

    // calculate text sizes
    const char* title = "SnakeXP";
    Vector2 titleSize = MeasureTextEx(GetFontDefault(), title, titleFontSize, 1);

    const char* startText = "Press [ENTER] to Start";
    Vector2 startSize = MeasureTextEx(GetFontDefault(), startText, menuFontSize, 1);

    const char* exitText = "Press [ESC] to Exit";
    Vector2 exitSize = MeasureTextEx(GetFontDefault(), exitText, menuFontSize, 1);

    // calculate text positions
    const int titleX = centerX - static_cast<int>(titleSize.x / 2);
    const int titleY = centerY - static_cast<int>(200 * scale);

    const int startX = centerX - static_cast<int>(startSize.x / 2);
    const int startY = centerY - static_cast<int>(startSize.y / 2);

    const int exitX = centerX - static_cast<int>(exitSize.x / 2);
    const int exitY = startY + menuFontSize * 2;

    // Draw main menu
    ClearBackground(background);

    DrawText(title, titleX, titleY, titleFontSize, drawColor);
    DrawText(startText, startX, startY, menuFontSize, drawColor);
    DrawText(exitText, exitX, exitY, menuFontSize, drawColor);
}

void GameLoop(const Color background, const Color drawColor, const int cellSize, const int cellCount,
    const int borderSize, const int scoreHeight, const float scale, const float scaleX, const float scaleY) {
    ClearBackground(background);
    DrawGame(drawColor, cellSize, cellCount, borderSize, scoreHeight, scale, scaleX, scaleY);
}