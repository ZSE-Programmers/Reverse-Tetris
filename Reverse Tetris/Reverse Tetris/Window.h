#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Window
{
public:
    Window();
    ~Window();

    void Create(int width, int height);

    SDL_Renderer*& GetRenderer() { return m_renderer; }
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};

