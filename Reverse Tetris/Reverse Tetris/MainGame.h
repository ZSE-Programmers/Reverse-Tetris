#pragma once
#include <SDL/SDL.h>
#include <list>

#include "Window.h"
#include "InputManager.h"
#include "Level.h"
#include "Sprite.h"
#include "Block.h"
#include "Shape.h"

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
	bool InsertBlock(int x, int y);
	void RemoveBlock();
	int FindBlock(glm::vec2 position);
	bool CanPlaceBlock(int x, int y, std::vector <std::string>& shape);

	void InitQueue();
	bool UpdateQueue();
	bool DrawQueue();
	void RemoveQueue();

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
	SDL_Texture* m_pinkSquare;

	// Shapes
	Shape LShape;
	Shape RLShape;
	Shape ZShape;
	Shape RZShape;
	Shape SQShape;
	Shape ZShape2;
	Shape RZShape2;

	Shape m_emptyShape;

	// Hold all blocks
	std::vector <Block*> m_blocks;

	// Number of types block
	std::vector <Shape> m_blockTypes;

	std::list <Shape> m_stackQueue;

	const int QUEUE_SIZE = 3;
	const glm::vec2 QUEUE_POSITIONS[3] = { {18, 2}, {18, 6}, {18, 10} };
	// Hold game state
	GameState m_gameState;

	// Keep level position 
	std::vector <std::string> m_levelData;

	const int TILE_WIDTH = 32;
};

