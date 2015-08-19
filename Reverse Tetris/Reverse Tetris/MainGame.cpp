#include "MainGame.h"
#include <iostream>
#include <random>
#include <ctime>

MainGame::MainGame()
{
	m_gameState = GameState::PLAY;
	m_type = 0;
}


MainGame::~MainGame()
{
	
}

void MainGame::Run()
{
	InitSystems();
	GameLoop();
}

void MainGame::InitSystems()
{
	// Creating window and getting renderer
	m_window.Create(800, 600);
	m_renderer = m_window.GetRenderer();

	m_levelData = m_level.GetLevelData();

	// Initalizing textures
	m_levelTexture = m_sprite.LoadTexture("Textures/bgtext.jpg", m_renderer);
	m_blueSquare = m_sprite.LoadTexture("Textures/element_blue_square.png", m_renderer);
	m_redSquare = m_sprite.LoadTexture("Textures/element_red_square.png", m_renderer);
	m_greenSquare = m_sprite.LoadTexture("Textures/element_green_square.png", m_renderer);
	m_purpleSquare = m_sprite.LoadTexture("Textures/element_purple_cube_glossy.png", m_renderer);
	m_yellowSquare = m_sprite.LoadTexture("Textures/element_yellow_square.png", m_renderer);

	InitBlocks();
	InitLevel();
}

void MainGame::GameLoop()
{
	while (m_gameState != GameState::EXIT)
	{
		ProcessInput();
		Update();
		Draw();
	}
}

void MainGame::Draw()
{
	SDL_RenderClear(m_renderer);
	
	// Draw level
	for (int y = 0; y < m_levelData.size(); y++)
	{
		for (int x = 0; x < m_levelData[y].size(); x++)
		{
			SDL_Rect destRect = { x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH };
			char tile = m_levelData[y][x];
			switch (tile)
			{
			case '#':
				SDL_RenderCopy(m_renderer, m_levelTexture, NULL, &destRect);
				break;
			case '1':
				SDL_RenderCopy(m_renderer, m_blueSquare, NULL, &destRect);
				break;
			case '2':
				SDL_RenderCopy(m_renderer, m_redSquare, NULL, &destRect);
				break;
			case '3':
				SDL_RenderCopy(m_renderer, m_greenSquare, NULL, &destRect);
				break;
			case '4':
				SDL_RenderCopy(m_renderer, m_purpleSquare, NULL, &destRect);
				break;
			case '5':
				SDL_RenderCopy(m_renderer, m_yellowSquare, NULL, &destRect);
				break;
			case '6':
				SDL_RenderCopy(m_renderer, m_greenSquare, NULL, &destRect);
				break;
			case '7':
				SDL_RenderCopy(m_renderer, m_greenSquare, NULL, &destRect);
				break;
			}
		}
	}
	SDL_RenderPresent(m_renderer);
}

void MainGame::Update()
{
	if (m_inputManager.IsButtonPressed())
	{
		RemoveBlock();
	}
}

void MainGame::ProcessInput()
{
	SDL_Event tmp_event;
	while (SDL_PollEvent(&tmp_event))
	{
		switch (tmp_event.type)
		{
		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			exit(1);
			break;
		case SDL_MOUSEMOTION:
			m_inputManager.SetMousePosition(glm::vec2(tmp_event.motion.x, tmp_event.motion.y));
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.PressButton();
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputManager.ReleaseButton();
			break;
		case SDL_KEYDOWN:
			m_inputManager.PressKey(tmp_event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputManager.ReleaseKey(tmp_event.key.keysym.sym);
			break;
		}
	}
}

void MainGame::InitBlocks()
{
	LShape.Init(m_type++, "Levels/LShape.txt");
	RLShape.Init(m_type++, "Levels/RLShape.txt");
	ZShape.Init(m_type++, "Levels/ZShape.txt");
	RZShape.Init(m_type++, "Levels/RZShape.txt");
	SQShape.Init(m_type++, "Levels/SQShape.txt");

	ZShape2.Init(m_type++, "Levels/ZShape2.txt");
	RZShape2.Init(m_type++, "Levels/RZShape2.txt");
}

void MainGame::InitLevel()
{
	int counter = 5;
	for (int y = m_levelData.size() - 1; y >= 0; y--)
	{
		for (int x = m_levelData[y].size() - 1; x >= 0; x--)
		{
			char tile = m_levelData[y][x];
			if (tile == '.')
			{
				if (InsertBlock(x, y))
				{
					counter--;
					if (counter == 0)
					{
						return;
					}
				}
			}
		}
	}
}

bool MainGame::InsertBlock(int x, int y)
{
	// Count pieces of block are fitting
	int counter = 0;

	// Rolling which block have to be fit
	static std::mt19937 randomEngine(time(NULL));
	static std::uniform_int_distribution <int> rollShape(1, 4);
	int roll = rollShape(randomEngine);
	
	// Vector for holding shape
	std::vector <std::string> shape;

	// Processing which which shape to draw
	switch (roll)
	{
	case 1:
		shape = RZShape.GetShape();
		break;
	case 2:
		shape = ZShape.GetShape();
		break;
	case 3:
		shape = ZShape2.GetShape();
		break;
	case 4:
		shape = RZShape2.GetShape();
		break;
	}

	// Check all tiles from shape 
	for (int i = 0; i < shape.size(); i++)
	{
		for (int j = 0; j < shape[i].size(); j++)
		{
			char tile = shape[i][j];
			if (tile != '.')
			{
				if (m_levelData[y + i][x + j] == '.')
				{
					counter++;
				}
			}
		}
	}

	// If all 4 tiles are empty we can draw our block
	if (counter == 4)
	{
		Block* tmp_block = new Block;
		for (int i = 0; i < shape.size(); i++)
		{
			for (int j = 0; j < shape[i].size(); j++)
			{
				char tile = shape[i][j];
				if (tile != '.')
				{
					m_levelData[y + i][x + j] = tile;
					tmp_block->Add(x + j, y + i);
				}
			}
		}
		m_blocks.push_back(tmp_block);
		return true;
	}
	else
	{
		return false;
	}
}

void MainGame::RemoveBlock()
{
	int counter = 0;
	glm::vec2 mousePosition = m_inputManager.GetMousePosition();

	mousePosition = glm::vec2(floor(mousePosition.x / TILE_WIDTH), floor(mousePosition.y / TILE_WIDTH));

	if (m_levelData[mousePosition.y][mousePosition.x] != '.')
	{
		for (int i = 0; i < m_blocks.size(); i++)
		{
			std::vector <glm::vec2> blockPosition = m_blocks[i]->GetPosition();
			for (int j = 0; j < blockPosition.size(); j++)
			{
				if (blockPosition[j].y - 1 == '.')
				{
					// something
					counter++;
				}
				else
				{
					for (int k = 0; k < blockPosition.size(); k++)
					{
						if (blockPosition[j].y - 1 == blockPosition[k].y)
						{
							// something
							counter++;
						}
					}
				}
			}
			if (counter == 4)
			{
				for (int j = 0; j < blockPosition.size(); j++)
				{
					m_levelData[blockPosition[j].y][blockPosition[j].x] = '.';
				}
				delete m_blocks[i];
				m_blocks[i] = m_blocks.back();
				m_blocks.pop_back();
			}
		}
	}
}
