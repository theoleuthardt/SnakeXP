#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H
#include <vector>
#include <string>
#include <iostream>
#include <dirent.h>
#include "raylib.h"

using namespace std;

class Food {
public:
    Vector2 position{};
    Color color{};
    int size;
    Texture2D texture{};

    Food(int cellSize, Color color, int positionX, int positionY);
    ~Food();

    void draw() const;

    void randomizePosition(int cellCount);

private:
    static vector<string> getPngFilesInDirectory(const string& directory) {
        vector<string> pngFiles;

        DIR* dir = opendir(directory.c_str());
        if (dir == nullptr) {
            cerr << "Error opening directory: " << directory << endl;
            return pngFiles;
        }

        dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (string filename = entry->d_name; filename.size() > 4 && filename.substr(filename.size() - 4) == ".png") {
                pngFiles.push_back(directory + "/" += filename);
            }
        }

        closedir(dir);
        return pngFiles;
    }

    static string getRandomPngFile(const vector<string>& pngFiles) {
        if (pngFiles.empty()) {
            cerr << "No PNG files found!" << endl;
            return "";
        }

        srand(static_cast<unsigned int>(time(nullptr)));

        const int randomIndex = random() % pngFiles.size();
        return pngFiles[randomIndex];
    }
};

#endif
