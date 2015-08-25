#include "Sprite.h"


Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

SDL_Texture* Sprite::LoadTexture(std::string filePath, SDL_Renderer* renderer)
{
    SDL_Surface* loadedImage = nullptr;
    SDL_Texture* texture = nullptr;
    loadedImage = IMG_Load(filePath.c_str());

    if (loadedImage != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    else
    {
        printf("SDL Error: %s\n", SDL_GetError());
    }
    return texture;
}