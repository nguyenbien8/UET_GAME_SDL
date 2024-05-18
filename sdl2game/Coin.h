#ifndef Coin_h
#define Coin_h
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
class Coin
{
public:
    Coin(int x, int y);
    ~Coin();
    int xCoin;
    int yCoin;
    bool collected = false;
    int frame = 0;
    SDL_Texture *coinTexture;
    SDL_Rect animation;
    SDL_Rect hitbox;
    void Update();
    void Render(int x, int y);
};
#endif // Coin_h
