#include "gameObjects.h"
#include "raylib.h"

Food::Food(const int cellSize, const Color color, const float positionX, const float positionY) {
    this->color = color;
    this->size = cellSize;
    this->position = {positionX, positionY};
}

void Food::draw() {
    DrawRectangle(position.x * size, position.y * size, size, size, color);
}

void Food::randomizePosition(const int cellCount) {
    position.x = GetRandomValue(0, cellCount - 1) * size;
    position.y = GetRandomValue(0, cellCount - 1) * size;
}