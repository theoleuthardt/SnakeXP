#include "gamesetup.h"
#include "raylib.h"
#include <iostream>

using namespace std;

void setupGame() {
    // initial game configuration
    InitWindow(1200, 1200, "SNAKE XP");
    SetTargetFPS(60);

    // game icon
    const Image icon = LoadImage("../assets/icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
}