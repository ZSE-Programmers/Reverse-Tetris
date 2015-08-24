#include "MainGame.h"
#include <iostream>
#include <random>
#include <ctime>

MainGame::MainGame()
{
	TTF_Init();
	m_gameState = GameState::PLAY;
	LANES = 0;
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
	InitBlocks();

	// Loading first blocks on map
	InitLevel();

	// Initalizing queue
	InitQueue();

	// Initalizing new blocks
	InitNewBlocks();
}

void MainGame::GameLoop()
{
	int counter = 0;
	while (m_gameState != GameState::EXIT)
	{
		m_fps.Start();

		ProcessInput();

		// If new blocks file is at the end we roll new blocks
		if (LANES == m_newBlocksData.size() - 2)
		{
			m_newBlocksData.clear();
			InitNewBlocks();
			LANES = 0;
		}

		counter++;
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
						m_levelData[y] = m_newBlocksData[LANES];
					}
				}
			}
			counter = 0;
			MoveUp();
			AddNewBlocks(LANES);
			LANES++;
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

void MainGame::InitBlocks()
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
	int counter = 10;
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
		if (CanPlaceBlock(x, y, shape))
		{
			m_blockTypes.push_back(RZShape);
			m_blocks.back()->AddShape(RZShape);
			return true;
		}
		break;
	case 2:
		shape = ZShape.GetShape();
		if (CanPlaceBlock(x, y, shape))
		{
			m_blockTypes.push_back(ZShape);
			m_blocks.back()->AddShape(ZShape);
			return true;
		}
		break;
	case 3:
		shape = ZShape2.GetShape();
		if (CanPlaceBlock(x, y, shape))
		{	
			m_blockTypes.push_back(ZShape);
			m_blocks.back()->AddShape(ZShape);
			return true;
		}
		break;
	case 4:
		shape = RZShape2.GetShape();
		if (CanPlaceBlock(x, y, shape))
		{
			m_blockTypes.push_back(RZShape);
			m_blocks.back()->AddShape(RZShape);
			return true;
		}
		break;
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
		int index = FindBlock(mousePosition);
		if (index != -1)
		{
			for (auto i = m_stackQueue.begin(); i != m_stackQueue.end(); i++)
			{
				if (i->GetShape() == m_blocks[index]->GetShape())
				{
					ProcessRemove(index, i);
					return;
				}
			}
		}
	}
}

int MainGame::FindBlock(glm::vec2 position)
{
	for (int i = 0; i < m_blocks.size(); i++)
	{
		std::vector <glm::vec2> blockPosition = m_blocks[i]->GetPosition();

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

bool MainGame::CanPlaceBlock(int x, int y, std::vector<std::string>& shape)
{
	int counter = 0;
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
		char tile;
		Block* tmp_block = new Block;
		for (int i = 0; i < shape.size(); i++)
		{
			for (int j = 0; j < shape[i].size(); j++)
			{
				tile = shape[i][j];
				if (tile != '.')
				{
					m_levelData[y + i][x + j] = tile;
					tmp_block->AddSquare(x + j, y + i);
				}
			}
		}
		m_blocks.push_back(tmp_block);
		return true;
	}
	return false;
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

void MainGame::InitNewBlocks()
{
	// Initalizing new blocks data
	std::ifstream file;
	std::string input;
	file.open("Levels/newlanes.txt");
	if (file.fail())
	{
		perror("Levels/newlanes.txt");
	}
	while (std::getline(file, input))
	{
		m_newBlocksData.push_back(input);
	}

	// Rolling new blocks
	for (int y = 0; y < m_newBlocksData.size(); y++)
	{
		for (int x = 0; x < m_newBlocksData[y].size(); x++)
		{
			char tile = m_newBlocksData[y][x];
			if (tile == '.')
			{
				RollNewBlock(x, y);
			}
		}
	}

	for (int i = 0; i < m_newBlocksData.size(); i++)
	{
		std::cout << m_newBlocksData[i] << std::endl;
	}
}

void MainGame::RollNewBlock(int x, int y)
{
	static std::mt19937 randomEngine(time(NULL));
	std::uniform_int_distribution <int> roll(1, 5);

	int newBlock = roll(randomEngine);
	switch (newBlock)
	{
	case 1:
		if (InsertNewBlock(x, y, ZShape.GetShape()))
		{
			m_newBlocks.back()->AddShape(ZShape);
		}
		break;
	case 2:
		if (InsertNewBlock(x, y, RZShape.GetShape()))
		{
			m_newBlocks.back()->AddShape(RZShape);
		}
		break;
	case 3:
		if (InsertNewBlock(x, y, LShape.GetShape()))
		{
			m_newBlocks.back()->AddShape(LShape);
		}
		break;
	case 4:
		if (InsertNewBlock(x, y, RLShape.GetShape()))
		{
			m_newBlocks.back()->AddShape(RLShape);
		}
		break;
	case 5:
		if (InsertNewBlock(x, y, SQShape.GetShape()))
		{
			m_newBlocks.back()->AddShape(SQShape);
		}
		break;
	case 6:
		break;
	case 7:
		break;
	}
}

bool MainGame::InsertNewBlock(int x, int y, std::vector<std::string>& shape)
{
	int counter = 0;
	// Check all tiles from shape 
	for (int i = 0; i < shape.size(); i++)
	{
		for (int j = 0; j < shape[i].size(); j++)
		{
			char tile = shape[i][j];
			if (tile != '.')
			{
				if (m_newBlocksData[y + i][x + j] == '.')
				{
					counter++;
				}
			}
		}
	}

	// If all 4 tiles are empty we can draw our block
	if (counter == 4)
	{
		char tile;
		Block* tmp_block = new Block;
		for (int i = 0; i < shape.size(); i++)
		{
			for (int j = 0; j < shape[i].size(); j++)
			{
				tile = shape[i][j];
				if (tile != '.')
				{
					m_newBlocksData[y + i][x + j] = tile;
					tmp_block->AddSquare(x + j, y + i);
				}
			}
		}
		
		m_newBlocks.push_back(tmp_block);
		return true;
	}
	return false;
}

void MainGame::AddNewBlocks(int lanes)
{
	for (int i = 0; i < m_newBlocksData[lanes].size(); i++)
	{
		char tile = m_newBlocksData[lanes][i];
		if (tile != '#' && tile != '.')
		{
			int index = FindNewBlock({ i, lanes });
			if (index != -1)
			{
				Block* tmp_block = new Block;
				std::vector <glm::vec2> blockPosition = m_newBlocks[index]->GetPosition();
				for (int i = 0; i < blockPosition.size(); i++)
				{
					tmp_block->AddSquare(blockPosition[i].x, blockPosition[i].y + 16 - lanes);
					std::cout << blockPosition[i].x << " " << blockPosition[i].y + 16 - lanes << std::endl;
				}
				m_blockTypes.push_back(m_newBlocks[index]->GetRealShape());
				tmp_block->AddShape(m_newBlocks[index]->GetRealShape());
				m_blocks.push_back(tmp_block);
				
				delete m_newBlocks[index];
				m_newBlocks[index] = m_newBlocks.back();
				m_newBlocks.pop_back();
			}
		}
	}

}

int MainGame::FindNewBlock(glm::vec2 position)
{
	for (int i = 0; i < m_newBlocks.size(); i++)
	{
		std::vector <glm::vec2> blocksPosition = m_newBlocks[i]->GetPosition();
		for (int j = 0; j < blocksPosition.size(); j++)
		{
			if (blocksPosition[j].x == position.x && blocksPosition[j].y == position.y)
			{
				return i;
			}
		}
	}
	return -1;
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
			std::cout << tmp_shape[i] << std::endl;
			for (int j = 0; j < tmp_shape[i].size(); j++)
			{
				char tile = tmp_shape[i][j];
				if (tile != '.')
				{
					m_levelData[QUEUE_POSITIONS[counter].y + i][QUEUE_POSITIONS[counter].x + j] = tile;
				}
			}
		}
		std::cout << "\n\n";
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

