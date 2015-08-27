#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

class Window
{
public:
    Window();
    ~Window();

    void Create(int width, int height);
    void RenderScore(int score, TTF_Font* font, SDL_Renderer* renderer, SDL_Texture* textTexture, float& time);
    SDL_Renderer*& GetRenderer() { return m_renderer; }
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};

