#include "gameSetup.h"
#include "raylib.h"
#include "snakeXP.h"

int main() {
    constexpr Color background = {9, 20, 227, 255};
    constexpr Color drawColor = {255, 255, 255, 255};
    constexpr int cellSize = 40;
    constexpr int cellCount = 30;

    setupGame(cellSize, cellCount);
    gameLoop(background, drawColor, cellSize, cellCount);
    return 0;
}
