#ifndef Trap_h
#define Trap_h
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

//Cam bay
class Trap
{
public:
    Trap(int x, int y, int type);
    ~Trap();
    void Update();
    void Render(int x, int y);
    SDL_Rect hitbox;
    SDL_Texture* trapoff;
    SDL_Texture* trapon;
    bool activated;
    int activatedTime;
    int xTrap, yTrap;
    int typeTrap;
};
#endif // Trap_h
