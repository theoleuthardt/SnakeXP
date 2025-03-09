#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#include <string>
#include <iostream>
#include <gameStates.h>
#include <map>
#include "raylib.h"

class Snake {
    Vector2 position{};
    Texture2D texture{};
    int size = 0;
    int velocity = 0;
    Direction direction = UP;
    int level = 0;
    float scale = 1.0f;
};

#endif
