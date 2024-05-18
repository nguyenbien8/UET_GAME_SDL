#ifndef Map_h
#define Map_h
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
class Map
{
public:
    Map(int level);
    ~Map();
    void LoadMap(int level);
    void DrawMap(SDL_Rect camera);
    std::vector<std::vector<int>> curr_map;
    SDL_Rect src;
    SDL_Rect dest;
    SDL_Texture *tile;
};
#endif
