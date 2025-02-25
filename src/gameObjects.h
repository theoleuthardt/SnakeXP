#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H
#include "raylib.h"

class Food {
public:
    Vector2 position;
    Color color;
    int size;

    Food(int cellSize, Color color, float positionX, float positionY);

    void draw();

    void randomizePosition(int cellCount);
};

#endif
