#include "gameSetup.h"
#include "raylib.h"
#include "snakeXP.h"

int main() {
    constexpr Color background = {9, 20, 227, 255};
    constexpr Color drawColor = {255, 255, 255, 255};
    constexpr int cellSize = 60;
    constexpr int cellCount = 20;

    SetupGame(cellSize, cellCount);
    GameLoop(background, drawColor, cellSize, cellCount);
    return 0;
}
