#include "MainGame.h"



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

	m_levelPosition = m_level.GetLevelPosition();

	// Initalizing textures
	m_levelTexture = m_sprite.LoadTexture("Textures/bgtext.jpg", m_renderer);
	m_blueSquare = m_sprite.LoadTexture("Textures/element_blue_square.png", m_renderer);
	m_redSquare = m_sprite.LoadTexture("Textures/element_red_square.png", m_renderer);
	m_greenSquare = m_sprite.LoadTexture("Textures/element_green_square.png", m_renderer);
	m_purpleSquare = m_sprite.LoadTexture("Textures/element_purple_cube_glossy.png", m_renderer);
	m_yellowSquare = m_sprite.LoadTexture("Textures/element_yellow_square.png", m_renderer);
}

void MainGame::GameLoop()
{
	while (true)
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
	for (auto i = m_levelPosition.begin(); i != m_levelPosition.end(); i++)
	{
		SDL_Rect destRect = { i->x, i->y, 32, 32 };
		SDL_RenderCopy(m_renderer, m_levelTexture, 0, &destRect);
	}



	SDL_RenderPresent(m_renderer);
}

void MainGame::Update()
{
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
			//std::cout << tmp_event.motion.x << " " << tmp_event.motion.y << std::endl;
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
	LShape.Init(m_level.GetLShape(), m_type++);
}
