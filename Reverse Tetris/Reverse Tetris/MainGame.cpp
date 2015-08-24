#include "MainGame.h"
#include <iostream>
#include <random>
#include <ctime>

MainGame::MainGame()
{
	TTF_Init();
	m_gameState = GameState::PLAY;
	m_newLines = 0;
	m_speed = 4;

	m_font = nullptr;
	m_font = TTF_OpenFont("Fonts/BEBAS.ttf", 32);
	if (m_font == nullptr)
	{
		std::cout << "Could not load font" << std::endl;
	}
	m_score = 0;
}

MainGame::~MainGame()
{
	for (int i = 0; i < m_blocks.size(); i++)
	{
		delete m_blocks[i];
	}
	for (int i = 0; i < m_newBlocks.size(); i++)
	{
		delete m_newBlocks[i];
	}
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
	m_levelTexture = m_sprite.LoadTexture("Textures/mountain.png", m_renderer);
	m_blueSquare = m_sprite.LoadTexture("Textures/element_blue_square.png", m_renderer);
	m_redSquare = m_sprite.LoadTexture("Textures/element_red_square.png", m_renderer);
	m_greenSquare = m_sprite.LoadTexture("Textures/element_green_square.png", m_renderer);
	m_purpleSquare = m_sprite.LoadTexture("Textures/element_purple_cube_glossy.png", m_renderer);
	m_yellowSquare = m_sprite.LoadTexture("Textures/element_yellow_square.png", m_renderer);
	m_pinkSquare = m_sprite.LoadTexture("Textures/pink_square.png", m_renderer);

	// Adding shapes for each block
	InitShapes();

	// Loading first blocks on map
	InitLevel();

	// Initalizing queue
	InitQueue();

	// Initalizing new blocks
	InitNewBlocks();
}

void MainGame::GameLoop()
{
	while (m_gameState != GameState::EXIT)
	{
		m_fps.Start();

		ProcessInput();

		// If new blocks txt file is at the end we roll new blocks
		if (m_newLines == m_newBlocksData.size() - 2)
		{
			m_newBlocksData.clear();
			InitNewBlocks();
			m_newLines = 0;
		}

		// Moving all blocks one tile up
		if (SDL_GetTicks() / 1000.0f > m_speed)
		{
			m_speed += 4 * 0.95;
			for (int y = 0; y < m_levelData.size(); y++)
			{
				for (int x = 0; x < m_levelData[y].size(); x++)
				{
					char tile = m_levelData[y][x];
					if (tile != '#' && tile != 'x' && tile != '-' && y != 1 && y != 16 && x < 14)
					{
						m_levelData[y][x] = m_levelData[y + 1][x];
					}
					else if (y == 16)
					{
						m_levelData[y] = m_newBlocksData[m_newLines];
					}
				}
			}
			MoveUp();
			AddNewBlocks(m_newLines);
			m_newLines++;
		}

		Update();
		Draw();

		m_fps.End();
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
			case '+':
				// Timer
				break;
			case '0':
				// Points
				break;
			}
		}
	}

	UpdateScore();

	SDL_RenderPresent(m_renderer);
}

void MainGame::Update()
{
	if (m_inputManager.IsButtonPressed())
	{
		RemoveBlock();
	}
	for (int i = 1; i < m_levelData[2].size(); i++)
	{
		if (i < 14)
		{
			if (m_levelData[2][i] != '.')
			{
				m_gameState = GameState::EXIT;
			}
		}
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

void MainGame::InitShapes()
{
	LShape.Init("Levels/LShape.txt", 1);
	RLShape.Init("Levels/RLShape.txt", 2);
	ZShape.Init("Levels/ZShape.txt", 3);
	RZShape.Init("Levels/RZShape.txt", 4);
	SQShape.Init("Levels/SQShape.txt", 5);

	ZShape2.Init("Levels/ZShape2.txt", 3);
	RZShape2.Init("Levels/RZShape2.txt", 4);

	m_emptyShape.Init("Levels/EmptyShape.txt", -1);
}

void MainGame::InitLevel()
{
	// How many blocks we want to spawn at the begining
	int counter = 10;
	for (int y = m_levelData.size() - 1; y >= 0; y--)
	{
		for (int x = m_levelData[y].size() - 1; x >= 0; x--)
		{
			if (InitBlocks({ x, y }))
			{
				counter--;
				if (counter <= 0)
				{
					// This means we are done
					return;
				}
			}
		}
	}
}

bool MainGame::InitBlocks(glm::vec2 position)
{
	if (m_levelData[position.y][position.x] == '.')
	{
		if (m_level.InsertBlock(position, m_levelData, m_blocks, { 3, 4 }, m_blockTypes))
		{
			return true;
		}
	}
	return false;
}

void MainGame::RemoveBlock()
{
	glm::vec2 mousePosition = m_inputManager.GetMousePosition();
	// Converting mouse screen coords to levelData coords
	mousePosition = glm::vec2(floor(mousePosition.x / TILE_WIDTH), floor(mousePosition.y / TILE_WIDTH));

	// Check if this is block or just a part of map
	if (m_levelData[mousePosition.y][mousePosition.x] != '.' &&
		mousePosition.x > 0 && mousePosition.x < 14 && mousePosition.y > 0 && mousePosition.y < 17)
	{
		// Return index to block we have to remove
		int index = FindBlock(mousePosition, m_blocks);
		if (index != -1)
		{
			for (auto i = m_stackQueue.begin(); i != m_stackQueue.end(); i++)
			{
				if (i->GetShape() == m_blocks[index]->GetShape().GetShape())
				{
					ProcessRemove(index, i);
					return;
				}
			}
		}
	}
}

void MainGame::ProcessRemove(int index, std::list<Shape>::iterator& it)
{
	// Check if we can remove block
	if (m_blocks[index]->CanRemove(m_levelData))
	{
		// Adding points to player score
		m_score += 10;

		// Processing queue
		RemoveQueue(it);
		UpdateQueue();
		DrawQueue();

		// Position of squares that we can to replace by '.'
		std::vector <glm::vec2> squarePosition = m_blocks[index]->GetPosition();
		// Deleting block
		delete m_blocks[index];
		m_blocks[index] = m_blocks.back();
		m_blocks.pop_back();
		// Replacing sqaures by '.'
		for (int i = 0; i < squarePosition.size(); i++)
		{
			m_levelData[squarePosition[i].y][squarePosition[i].x] = '.';
		}
	}
}

int MainGame::FindBlock(glm::vec2 position, std::vector <Block*>& blocks)
{
	for (int i = 0; i < blocks.size(); i++)
	{
		std::vector <glm::vec2> blockPosition = blocks[i]->GetPosition();

		for (int j = 0; j < blockPosition.size(); j++)
		{
			if (blockPosition[j] == position)
			{
				return i;
			}
		}
	}
	return -1;
}

void MainGame::MoveUp()
{
	for (int i = 0; i < m_blocks.size(); i++)
	{
		std::vector <glm::vec2> blockPosition = m_blocks[i]->GetPosition();
		for (int j = 0; j < blockPosition.size(); j++)
		{
			blockPosition[j].y -= 1;
		}
		m_blocks[i]->SetPosition(blockPosition);
	}
}

void MainGame::InitNewBlocks()
{
	m_level.InitNewBlocks(m_newBlocks);

	m_newBlocksData = m_level.GetNewLinesData();

	// Rolling new blocks
	for (int y = 0; y < m_newBlocksData.size(); y++)
	{
		for (int x = 0; x < m_newBlocksData[y].size(); x++)
		{
			char tile = m_newBlocksData[y][x];
			if (tile == '.')
			{
				if (m_level.InsertBlock({ x, y }, m_newBlocksData, m_newBlocks, { 1, 5 }, m_blockTypes))
				{
					// Some stuff
				}
			}
		}
	}
}

void MainGame::AddNewBlocks(int newLines)
{
	for (int i = 0; i < m_newBlocksData[m_newLines].size(); i++)
	{
		char tile = m_newBlocksData[newLines][i];
		if (tile != '#' && tile != '.')
		{
			int index = FindBlock({ i, newLines }, m_newBlocks);
			if (index != -1)
			{
				Block* tmp_block = new Block;
				std::vector <glm::vec2> blockPosition = m_newBlocks[index]->GetPosition();
				for (int i = 0; i < blockPosition.size(); i++)
				{
					tmp_block->AddSquare(blockPosition[i].x, blockPosition[i].y + 16 - newLines);
				}
				m_blockTypes.push_back(m_newBlocks[index]->GetShape());
				tmp_block->AddShape(m_newBlocks[index]->GetShape());
				m_blocks.push_back(tmp_block);
				
				delete m_newBlocks[index];
				m_newBlocks[index] = m_newBlocks.back();
				m_newBlocks.pop_back();
			}
		}
	}
}

// Queue functions
// Initalizing, updating, drawing and removing blocks in queue

void MainGame::InitQueue()
{
	if (!m_blockTypes.empty())
	{
		// Pushing new blocks to the queue
		for (int i = 0; i < QUEUE_SIZE; i++)
		{
			// Random generator
			std::mt19937 randomEngine(time(NULL));
			std::uniform_int_distribution <int> roll(0, m_blockTypes.size() - 1);
			int index = roll(randomEngine);

			// Adding block to queue and removing from blocks 
			m_stackQueue.push_back(m_blockTypes[index]);
			m_blockTypes[index] = m_blockTypes.back();
			m_blockTypes.pop_back();
		}
	}

	// Drawing queue
	DrawQueue();
}

bool MainGame::UpdateQueue()
{
	// If we deleted all blocks we are quiting game
	if (m_blockTypes.empty())
	{
		m_stackQueue.push_back(m_emptyShape);
		return false;
	}
	else
	{
		std::mt19937 randomEngine(time(NULL));
		std::uniform_int_distribution <int> roll(0, m_blockTypes.size() - 1);
		int index = -1;
		index = roll(randomEngine);

		m_stackQueue.push_back(m_blockTypes[index]);
		m_blockTypes[index] = m_blockTypes.back();
		m_blockTypes.pop_back();

		return true;
	}
}

bool MainGame::DrawQueue()
{
	int counter = 0;
	for (auto it = m_stackQueue.begin(); it != m_stackQueue.end(); it++)
	{
		std::vector <std::string> tmp_shape = it->GetShape();
		for (int i = 0; i < tmp_shape.size(); i++)
		{
			for (int j = 0; j < tmp_shape[i].size(); j++)
			{
				char tile = tmp_shape[i][j];
				if (tile != '.')
				{
					m_levelData[QUEUE_POSITIONS[counter].y + i][QUEUE_POSITIONS[counter].x + j] = tile;
				}
			}
		}
		counter++;
	}
	return true;
}

void MainGame::RemoveQueue(std::list<Shape>::iterator& it)
{
	int counter = 0;
	for (auto it = m_stackQueue.begin(); it != m_stackQueue.end(); it++)
	{
		std::vector <std::string> tmp_shape = it->GetShape();
		for (int i = 0; i < tmp_shape.size(); i++)
		{
			for (int j = 0; j < tmp_shape[i].size(); j++)
			{
				m_levelData[QUEUE_POSITIONS[counter].y + i][QUEUE_POSITIONS[counter].x + j] = '.';
			}
		}
		counter++;
	}
	m_stackQueue.erase(it);
}

void MainGame::UpdateScore()
{
	// Updating player score
	std::string str = std::to_string(m_score);
	SDL_Color textColor = { 255, 255, 255, 255 };

	SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, str.c_str(), textColor);
	if (textSurface == NULL)
	{
		std::cout << "Unable to create text surface!" << std::endl;
	}
	else
	{
		m_textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
		if (m_textTexture == NULL)
		{
			std::cout << "Unable to create text texture!\n";
		}

		SDL_FreeSurface(textSurface);
	}

	SDL_Rect destRect = { 550, 473, 100, 38 };

	SDL_RenderCopy(m_renderer, m_textTexture, 0, &destRect);


	// Updating player time 
	str = std::to_string(SDL_GetTicks()/1000.0f);


	textSurface = TTF_RenderText_Solid(m_font, str.c_str(), textColor);
	if (textSurface == NULL)
	{
		std::cout << "Unable to create text surface!" << std::endl;
	}
	else
	{
		m_textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
		if (m_textTexture == NULL)
		{
			std::cout << "Unable to create text texture!\n";
		}

		SDL_FreeSurface(textSurface);
	}
	destRect = { 550, 538, 100, 38 };

	SDL_RenderCopy(m_renderer, m_textTexture, 0, &destRect);
}

