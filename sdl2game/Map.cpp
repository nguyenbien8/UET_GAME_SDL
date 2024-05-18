#include "Game.h"
#include "Map.h"
#include "TextureManager.h"
Map::Map(int level)
{
    src.x = 0; src.y = 0; src.w = 32; src.h = 32;
    dest.x = 0; dest.y = 0; dest.w = 32; dest.h = 32;
    tile = TextureManager::LoadTexture("Assets/Map/tile.png");
    LoadMap(level);
}
Map::~Map() {
    if (tile != nullptr) {
        SDL_DestroyTexture(tile);
        tile = nullptr;
    }
}

//FULLMAP
void Map::LoadMap(int level)
{
    std::string filename = "Assets/Map/level" + std::to_string(level) + ".txt";
    std::ifstream file(filename);
    int width, height;
    if (level == 1) {width = 53; height = 73;}
    if (level == 2) {width = 66; height = 110;}
    curr_map.resize(height, std::vector<int>(width));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) {file >> curr_map[i][j];}
    }
    file.close();
}

//MAP OF SCREEN_FILL_MAP
void Map::DrawMap(SDL_Rect camera)
{
    for (int i = 0; i < 21; i++){
        for (int j = 0; j < 31; j++)
        {
            dest.x = j * 32; dest.y = i * 32;
            int ID = curr_map[i+camera.y/32][j+camera.x/32];
            if (ID % 19 == 0) {src.y = (ID / 19 - 1) * 32; src.x = 18 * 32;}
            else {src.y = (ID / 19) * 32; src.x = (ID % 19 - 1) * 32;}
            TextureManager::Draw(tile, src, dest);
        }
    }
}
