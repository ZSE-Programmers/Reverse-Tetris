#pragma once
#include <SDL/SDL.h>

#include "Window.h"
#include "InputManager.h"
#include "Level.h"
#include "Sprite.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void Run();

private:
	// Functions
	void InitSystems();
	void GameLoop();
	void Draw();
	void Update();
	void ProcessInput();

	// Classes
	Window m_window;
	InputManager m_inputManager;
	Level m_level;
	Sprite m_sprite;

	// Game renderer
	SDL_Renderer* m_renderer;

	SDL_Texture* m_levelTexture;

	// Hold game state
	GameState m_gameState;

	// Keep level position in vec2
	std::vector <glm::vec2> m_levelPosition;

};

