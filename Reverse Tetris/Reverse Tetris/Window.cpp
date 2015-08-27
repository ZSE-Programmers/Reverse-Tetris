#include "Window.h"
#include <stdio.h>
#include <string>
#include <iostream>


Window::Window() 
{
}


Window::~Window()
{
}

void Window::Create(int width, int height)
{
    // Creating window
    m_window = SDL_CreateWindow("Reverse Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    // Create renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    // Error checking
    if (m_renderer == nullptr)
    {
        printf("We were not able to create the renderer! SDL Error: %s\n", SDL_GetError());
        return;
    }
    // Set background color
    SDL_SetRenderDrawColor(m_renderer, 60, 30, 30, 255);

    int imgFlags = IMG_INIT_PNG;
    // Error checking
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not be initialized! SDL_image Error: %s\n", IMG_GetError());
        return;
    }
}

void Window::RenderScore(int score, TTF_Font* font, SDL_Renderer* renderer, SDL_Texture* textTexture, float& time)
{
    std::string str = std::to_string(score);
    SDL_Color textColor = { 255, 255, 255, 255 };

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, str.c_str(), textColor);
    if (textSurface == NULL)
    {
        std::cout << "Unable to create text surface!" << std::endl;
    }
    else
    {
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture == NULL)
        {
            std::cout << "Unable to create text texture!\n";
        }

        SDL_FreeSurface(textSurface);
    }

    SDL_Rect destRect = { 550, 473, 100, 38 };

    SDL_RenderCopy(renderer, textTexture, 0, &destRect);


    // Updating player time 
    float tmp_time = (SDL_GetTicks() / 1000.0f) - time;
    std::cout << tmp_time << std::endl;
    str = std::to_string(tmp_time);


    textSurface = TTF_RenderText_Solid(font, str.c_str(), textColor);
    if (textSurface == NULL)
    {
        std::cout << "Unable to create text surface!" << std::endl;
    }
    else
    {
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture == NULL)
        {
            std::cout << "Unable to create text texture!\n";
        }

        SDL_FreeSurface(textSurface);
    }
    destRect = { 550, 538, 100, 38 };

    SDL_RenderCopy(renderer, textTexture, 0, &destRect);
}

