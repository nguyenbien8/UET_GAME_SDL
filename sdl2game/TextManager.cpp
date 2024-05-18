#include "Game.h"
#include "TextManager.h"

TextManager::TextManager(int fontSize) {
    textFont = TTF_OpenFont("Assets/Font/myfont.ttf", fontSize);
    textTexture = nullptr;
    textSurface = nullptr;
}
void TextManager::Render(std::string textstr, int x, int y, bool middle)
{
    const char* text = textstr.c_str();
    textColor = {255,255,255};
    textSurface = TTF_RenderText_Solid(textFont, text, textColor);
    textTexture = SDL_CreateTextureFromSurface(Game::gRenderer, textSurface);
    SDL_Rect dest = {x, y, textSurface->w, textSurface->h};
    if (middle)
    {
        dest.x = x - textSurface->w / 2;
        dest.y = y - textSurface->h / 2;
    }
    else
    {
        dest.x = x;
        dest.y = y;
    }
    SDL_RenderCopy(Game::gRenderer, textTexture, nullptr, &dest);
}
TextManager::~TextManager()
{
    TTF_CloseFont(textFont);
    textFont = nullptr;
    SDL_DestroyTexture(textTexture);
    textTexture = nullptr;
    SDL_FreeSurface(textSurface);
    textSurface = nullptr;
}
