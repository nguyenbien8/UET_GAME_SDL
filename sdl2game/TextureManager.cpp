#include "Game.h"
#include "TextureManager.h"
SDL_Texture* TextureManager::LoadTexture(const char* pngfile)
{
    SDL_Surface *tempSurface = IMG_Load(pngfile);
    SDL_Texture *tempTexture = SDL_CreateTextureFromSurface(Game::gRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tempTexture;
}
void TextureManager::Draw (SDL_Texture *texture, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(Game::gRenderer, texture, &src, &dest);
}
