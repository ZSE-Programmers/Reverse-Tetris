#pragma once
#include <SDL/SDL.h>

#include "Window.h"
#include "InputManager.h"
#include "Level.h"
#include "Sprite.h"
#include "Block.h"

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
	void InitBlocks();
	void InitLevel();
	void InsertBlock(int x, int y);

	// Classes
	Window m_window;
	InputManager m_inputManager;
	Level m_level;
	Sprite m_sprite;

	// Game renderer
	SDL_Renderer* m_renderer;

	// Textures
	SDL_Texture* m_levelTexture;
	SDL_Texture* m_blueSquare;
	SDL_Texture* m_redSquare;
	SDL_Texture* m_greenSquare;
	SDL_Texture* m_purpleSquare;
	SDL_Texture* m_yellowSquare;

	// Shapes
	Block LShape;
	Block ZShape;

	// Number of types block
	int m_type;

	// Hold game state
	GameState m_gameState;

	// Keep level position 
	std::vector <std::string> m_levelData;

	const int TILE_WIDTH = 32;

};

