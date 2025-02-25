#include <iostream>
#include

using namespace std;

int main() {
    cout << "Starting the game... pls wait!" << endl;
    InitWindow(800, 800, "SNAKE GAME");
    SetTargetFPS(60);

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Welcome to the Snake Game!", 100, 100, 20, LIGHTGRAY);
        EndDrawing();
    }

    return 0;
}