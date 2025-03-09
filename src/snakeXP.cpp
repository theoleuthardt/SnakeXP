#include <iostream>
#include "raylib.h"
#include "snakeXP.h"
#include "gameObjects/textureGrid.h"

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

void DrawGame(const int cellSize, const int cellCount, const int borderSize,
    const int scoreHeight, const float scale) {
    static SnakeTextureGrid textureGrid(cellSize, cellCount);
    static bool texturesLoaded = false;

    // calculate scaled values
    const int scaledCellSize = cellSize * scale;
    const int scaledBorderSize = borderSize * scale;
    constexpr float minScoreHeight = 40.0f;
    const float scaledScoreHeight = scoreHeight * scale;
    const int finalScoreHeight = static_cast<int>(max(scaledScoreHeight, minScoreHeight));


    // calculate offsets to center the game area
    int offsetX = (GetScreenWidth() - scaledCellSize * cellCount) / 2;
    int offsetY = scaledBorderSize + finalScoreHeight;

    if (!texturesLoaded) {
        texturesLoaded = textureGrid.loadTextures("assets");
        if (!texturesLoaded) {
            DrawText("Error loading textures!", offsetX + 200 * scale, offsetY + 200 * scale, 20 * scale, RED);
            return;
        }
    }

    ClearBackground(BLACK);

    const int scaledGameAreaWidth = scaledCellSize * cellCount;
    const int scaledGameAreaHeight = scaledCellSize * cellCount;
    DrawRectangle(offsetX, offsetY, scaledGameAreaWidth, scaledGameAreaHeight, BLACK);

    DrawRectangle(offsetX, scaledBorderSize, scaledGameAreaWidth, finalScoreHeight - 10 * scale, WHITE);

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
    SetWindowMinSize(600, 600);

    // game icon
    const Image icon = LoadImage("assets/icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
}

void DrawMainMenu(const float backgroundSpeed, const float scale) {
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const int centerX = screenWidth / 2;
    const int centerY = screenHeight / 2;

    // calculate scaled values
    const float titleFontSize = 100 * scale;
    const int roundedTitleFontSize = static_cast<int>(titleFontSize);
    const float menuFontSize = 30 * scale;
    const int roundedMenuFontSize = static_cast<int>(menuFontSize);

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
    const int exitY = startY + roundedMenuFontSize * 2;

    // dynamic background color
    const float time = static_cast<float>(GetTime()) * backgroundSpeed;
    const Color gradientColor = {
        static_cast<unsigned char>(127 + 127 * sin(time)),
        static_cast<unsigned char>(127 + 127 * sin(time + 2.0f)),
        static_cast<unsigned char>(127 + 127 * sin(time + 4.0f)),
        255
    };

    // Draw main menu
    ClearBackground(gradientColor);

    const int outlineSize = static_cast<int>(5 * scale);
    constexpr Color outlineColor = BLACK;

    DrawText(title, titleX - outlineSize, titleY, roundedTitleFontSize, outlineColor);
    DrawText(title, titleX + outlineSize, titleY, roundedTitleFontSize, outlineColor);
    DrawText(title, titleX, titleY - outlineSize, roundedTitleFontSize, outlineColor);
    DrawText(title, titleX, titleY + outlineSize, roundedTitleFontSize, outlineColor);
    DrawText(title, titleX, titleY, roundedTitleFontSize, WHITE);

    DrawText(startText, startX - outlineSize, startY, roundedMenuFontSize, outlineColor);
    DrawText(startText, startX + outlineSize, startY, roundedMenuFontSize, outlineColor);
    DrawText(startText, startX, startY - outlineSize, roundedMenuFontSize, outlineColor);
    DrawText(startText, startX, startY + outlineSize, roundedMenuFontSize, outlineColor);
    DrawText(startText, startX, startY, roundedMenuFontSize, WHITE);

    DrawText(exitText, exitX - outlineSize, exitY, roundedMenuFontSize, outlineColor);
    DrawText(exitText, exitX + outlineSize, exitY, roundedMenuFontSize, outlineColor);
    DrawText(exitText, exitX, exitY - outlineSize, roundedMenuFontSize, outlineColor);
    DrawText(exitText, exitX, exitY + outlineSize, roundedMenuFontSize, outlineColor);
    DrawText(exitText, exitX, exitY, roundedMenuFontSize, WHITE);
}

void GameLoop(const int cellSize, const int cellCount,
    const int borderSize, const int scoreHeight, const float scale) {
    DrawGame(cellSize, cellCount, borderSize, scoreHeight, scale);
}