#ifndef Player_h
#define Player_h
#include "Game.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
class Player
{
public:
    Player(const char* pngfile, int x, int y);
    ~Player();
    void Handle(SDL_Event e, Game* game, Map *map);
    void Update(SDL_Rect &camera, int x, int y);
    void Render();
    bool Collision(SDL_Rect hitbox);

    int xpos, ypos;
    double degrees;
    SDL_RendererFlip flip;

    SDL_Rect animation;
    SDL_Texture* playerTexture;
};
#endif
