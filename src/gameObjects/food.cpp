#include "food.h"
#include "raylib.h"

using namespace std;

Vector2 GetRandomPositions(const int cellCount) {
    const float x = static_cast<float>(GetRandomValue(0, cellCount - 1));
    const float y = static_cast<float>(GetRandomValue(0, cellCount - 1));
    return Vector2{x, y};
}

Food::Food(const int cellSize, const int cellCount, const Color color) {
    this->color = color;
    this->size = cellSize;
    this->position = GetRandomPositions(cellCount);

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

void Food::Draw() const {
    const Vector2 positions = {position.x * static_cast<float>(size), position.y * static_cast<float>(size)};
    const float scale = static_cast<float>(size) / static_cast<float>(texture.width);
    DrawTextureEx(texture, positions, 0.0f, scale, color);
}