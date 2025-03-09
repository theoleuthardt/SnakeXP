#include "textureGrid.h"
#include <iostream>

using namespace std;

SnakeTextureGrid::SnakeTextureGrid(const int cellSize, const int cellCount) {
    this->cellSize = cellSize;
    this->cellCount = cellCount;
    textures.resize(TEXTURE_COUNT);
    initTextureMap();
}

SnakeTextureGrid::~SnakeTextureGrid() {
    for (const auto& texture : textures) {
        UnloadTexture(texture);
    }
}

void SnakeTextureGrid::initTextureMap() {
    for (int i = 0; i < TEXTURE_COUNT; i++) {
        textureMap[static_cast<TextureType>(i)] = i;
    }
}

bool SnakeTextureGrid::loadTextures(const string& basePath) {
    const char* snakeFiles[5] = {
        "snake_up.png",
        "snake_down.png",
        "snake_left.png",
        "snake_right.png",
        "snake_body.png"
    };

    const char* foodFiles[5] = {
        "apple.png",
        "goldenapple.png",
        "greenapple.png",
        "cherry.png",
        "cookie.png"
    };

    const char* brickFiles[6] = {
        "brick_up.png",
        "brick_down.png",
        "brick_left.png",
        "brick_right.png",
        "brick_horizontal.png",
        "empty.png"
    };

    string snakePath = basePath + "/snake/";
    for (int i = 0; i < 5; i++) {
        string fullPath = snakePath + snakeFiles[i];
        textures[i] = LoadTexture(fullPath.c_str());
        if (textures[i].id == 0) {
            cerr << "Failed to load texture: " << fullPath << endl;
            return false;
        }
    }

    string foodPath = basePath + "/food/";
    for (int i = 0; i < 5; i++) {
        string fullPath = foodPath + foodFiles[i];
        textures[5 + i] = LoadTexture(fullPath.c_str());
        if (textures[5 + i].id == 0) {
            cerr << "Failed to load texture: " << fullPath << endl;
            return false;
        }
    }

    string brickPath = basePath + "/bricks/";
    for (int i = 0; i < 6; i++) {
        string fullPath = brickPath + brickFiles[i];
        textures[10 + i] = LoadTexture(fullPath.c_str());
        if (textures[10 + i].id == 0) {
            cerr << "Failed to load texture: " << fullPath << endl;
            return false;
        }
    }

    return true;
}

void SnakeTextureGrid::drawTextureAt(const TextureType type, const int gridX, const int gridY,
                                     const int offsetX, const int offsetY, const float scale) {
    if (textureMap.contains(type)) {
        const int index = textureMap[type];

        const float actualCellSize = cellSize * scale;
        const float textureScale = actualCellSize / max(textures[index].width, textures[index].height);

        const float scaledWidth = textures[index].width * textureScale;
        const float scaledHeight = textures[index].height * textureScale;
        SetTextureFilter(textures[index], TEXTURE_FILTER_POINT);

        float posX = gridX * actualCellSize + (actualCellSize - scaledWidth) / 2 + offsetX;
        float posY = gridY * actualCellSize + (actualCellSize - scaledHeight) / 2 + offsetY;

        const Rectangle source = { 0.0f, 0.0f, static_cast<float>(textures[index].width),
                                  static_cast<float>(textures[index].height) };
        const Rectangle dest = { posX, posY, scaledWidth, scaledHeight };

        DrawTexturePro(textures[index], source, dest, Vector2{0, 0}, 0.0f, WHITE);
    }
}



TextureType SnakeTextureGrid::getSnakePartTexture(const Vector2 current, const Vector2 prev, const Vector2 next,
                                                  const bool isTail, const bool isHead) {
    if (isHead) {
        if (next.y > current.y) return SNAKE_DOWN;
        if (next.y < current.y) return SNAKE_UP;
        if (next.x > current.x) return SNAKE_RIGHT;
        if (next.x < current.x) return SNAKE_LEFT;
    } else if (isTail) {
        if (prev.y > current.y) return SNAKE_DOWN;
        if (prev.y < current.y) return SNAKE_UP;
        if (prev.x > current.x) return SNAKE_RIGHT;
        if (prev.x < current.x) return SNAKE_LEFT;
    } else {
        if (prev.x < current.x && next.x > current.x || prev.x > current.x && next.x < current.x) return SNAKE_BODY;
        if (prev.y < current.y && next.y > current.y || prev.y > current.y && next.y < current.y) return SNAKE_BODY;
    }
    return SNAKE_BODY;
}