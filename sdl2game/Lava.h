#ifndef Lava_h
#define Lava_h
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
class Lava
{
public:
    Lava(int x, int y);
    ~Lava();
    int xLava;
    int yLava;
    void Update();
    void Render(int x, int y);
    SDL_Rect hitbox;
    SDL_Texture* lavaTexture;
};
#endif // Lava_h
