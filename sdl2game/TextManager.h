#ifndef TextManager_h
#define TextManager_h
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
class TextManager
{
public:
    TTF_Font* textFont;
    SDL_Texture* textTexture;
    SDL_Surface* textSurface;
    SDL_Color textColor;
    TextManager(int fontSize);
    ~TextManager();
    void Render(std::string textstr, int x, int y, bool middle);
};
#endif
