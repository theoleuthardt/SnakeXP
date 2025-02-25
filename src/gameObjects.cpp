#include "gameObjects.h"
#include "raylib.h"

using namespace std;

Food::Food(const int cellSize, const Color color, const int positionX, const int positionY) {
    this->color = color;
    this->size = cellSize;
    this->position = {static_cast<float>(positionX), static_cast<float>(positionY)};

    const vector<string> pngFiles = getPngFilesInDirectory("assets/food");
    const string randomPng = getRandomPngFile(pngFiles);

    if (!randomPng.empty()) {
        this->texture = LoadTexture(randomPng.c_str());
        cout << "Food texture loaded from: " << randomPng << endl;
    } else {
        cerr << "No PNG files found in directory!" << endl;
    }
}

Food::~Food() {
    UnloadTexture(texture);
}

void Food::draw() const {
    DrawTexture(texture, static_cast<int>(position.x) * size, static_cast<int>(position.y) * size, color);
}

void Food::randomizePosition(const int cellCount) {
    position.x = static_cast<float>(GetRandomValue(0, cellCount - 1));
    position.y = static_cast<float>(GetRandomValue(0, cellCount - 1));
}