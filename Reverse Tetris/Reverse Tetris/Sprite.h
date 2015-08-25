#pragma once
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
class Sprite
{
public:
    Sprite();
    ~Sprite();
    SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderer);
};

