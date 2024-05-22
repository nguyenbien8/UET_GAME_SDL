#include "Game.h"
#include "Map.h"
#include "TextureManager.h"
#include "Player.h"

Player::Player(const char* pngfile, int x, int y)
{
    x *= 32;
    y *= 32;
    playerTexture = TextureManager::LoadTexture(pngfile);
    xpos = x; ypos = y;
}
Player::~Player()
{
    if (playerTexture != nullptr) {
        SDL_DestroyTexture(playerTexture);
        playerTexture = nullptr;
    }
}

bool Player::Collision(SDL_Rect hitbox)
{
    if(xpos + 32 <= hitbox.x || hitbox.x + hitbox.w <= xpos || ypos + 32 <= hitbox.y || hitbox.y + hitbox.h <= ypos) return false;
    return true;
}

//HAM XU LY
void Player::Handle(SDL_Event e, Game* game, Map *map)
{
    switch(e.key.keysym.sym)
    {
    case SDLK_ESCAPE:
        game->isPause = true;
        break;
    case SDLK_DOWN:
        flip = SDL_FLIP_NONE; degrees = +90;
        while(1)
        {
            //MAP Text = id + 1;
            int type = map->curr_map[ypos/32+1][xpos/32];
            if(type == 118) { Mix_PlayChannel(-1,game->gChunk4,0); game->isWin = true; break; }
            if(type == 124 || type == 130 || type == 131) { Mix_PlayChannel(-1,game->gChunk6,0); game->isLose = true; break;}
            if(type <= 51)
            {
                break;
            }
            ypos += 1; game->updateGame(1); game->renderGame();
        }
        break;
    case SDLK_UP:
        flip = SDL_FLIP_NONE; degrees = -90;
        while(1)
        {
            int type = map->curr_map[(ypos-1)/32][xpos/32];
            if(type == 118) { Mix_PlayChannel(-1,game->gChunk4,0); game->isWin = true; break; }
            if (type == 127 || type == 126 || type == 129){ Mix_PlayChannel(-1,game->gChunk6,0); game->isLose = true; break;}

            if(type <= 51)
            {
                break;
            }
            ypos -= 1; game->updateGame(1); game->renderGame();
        }
        break;
    case SDLK_RIGHT:
        flip = SDL_FLIP_NONE; degrees = 0;
        while(1)
        {
            int type = map->curr_map[ypos/32][xpos/32+1];
            if(type == 118) { Mix_PlayChannel(-1,game->gChunk4,0); game->isWin = true; break; }
            if(type == 128 || type == 130 || type == 129) { Mix_PlayChannel(-1,game->gChunk6,0); game->isLose = true; break;}
            if(type <= 51)
            {
                break;
            }
            xpos += 1; game->updateGame(1); game->renderGame();
        }
        break;
    case SDLK_LEFT:
        flip = SDL_FLIP_HORIZONTAL; degrees = 0;
        while(1)
        {
            int type = map->curr_map[ypos/32][(xpos-1)/32];
            if(type == 118) { Mix_PlayChannel(-1,game->gChunk4,0); game->isWin = true; break; }
            if(type == 125 || type == 126 || type == 131) { Mix_PlayChannel(-1,game->gChunk6,0); game->isLose = true; break;}
            if(type <= 51)
            {
                break;
            }
            xpos -= 1; game->updateGame(1); game->renderGame();
        }
        break;
    }
}
void Player::Update(SDL_Rect &camera, int x, int y)
{
    camera.x = x - 480; camera.y = y - 320;
}
void Player::Render()
{
    SDL_Rect temp = {480,320,32,32};
    SDL_RenderCopyEx(Game::gRenderer, playerTexture, NULL, &temp, degrees, NULL, flip);
}
