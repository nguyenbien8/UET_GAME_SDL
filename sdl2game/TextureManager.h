#ifndef TextureManager_h
#define TextureManager_h
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
class TextureManager
{
public:
    static SDL_Texture* LoadTexture (const char* pngfile);
    static void Draw (SDL_Texture *texture, SDL_Rect src, SDL_Rect dest);
};
#endif
