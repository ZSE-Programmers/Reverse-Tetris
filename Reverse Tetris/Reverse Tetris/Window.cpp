#include "Window.h"
#include <stdio.h>

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
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

    int imgFlags = IMG_INIT_PNG;
    // Error checking
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not be initialized! SDL_image Error: %s\n", IMG_GetError());
        return;
    }
}

