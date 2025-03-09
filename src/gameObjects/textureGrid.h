#ifndef TEXTUREGRID_H
#define TEXTUREGRID_H
#include "raylib.h"
#include <vector>
#include <map>

using namespace std;

enum TextureType {
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_LEFT,
    SNAKE_RIGHT,
    SNAKE_BODY,
    APPLE,
    GOLDEN_APPLE,
    GREEN_APPLE,
    CHERRY,
    COOKIE,
    BRICK_UP,
    BRICK_DOWN,
    BRICK_LEFT,
    BRICK_RIGHT,
    BRICK_HORIZONTAL,
    EMPTY,
    TEXTURE_COUNT
};

class SnakeTextureGrid {
    vector<Texture2D> textures;
    int cellSize;
    int cellCount;
    map<TextureType, int> textureMap;

public:
    SnakeTextureGrid(int cellSize, int cellCount);
    ~SnakeTextureGrid();

    void initTextureMap();
    bool loadTextures(const string& basePath);
    void drawTextureAt(TextureType type, int gridX, int gridY, int offsetX, int offsetY, float scale);

    static TextureType getSnakePartTexture (Vector2 current, Vector2 prev, Vector2 next,
                                          bool isTail = false, bool isHead = false);
};

#endif