#include "Game.h"
Game* game = nullptr;
int main(int argc, char* args[])
{
    const int FPS = 60;
    const int frameDelay = 1000/FPS;
    Uint32 frameStart;
    int frameTime;
    game = new Game;
    game->initGame();
    while (game->isRunning)
    {
        frameStart = SDL_GetTicks();
        if(game->changeState == true) game->changeState = false;
        game->handleEvent();
        game->updateGame(0);
        if(game->changeState == false) game->renderGame();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) SDL_Delay(frameDelay-frameTime);
    }
    game->closeGame();
    return 0;
}
