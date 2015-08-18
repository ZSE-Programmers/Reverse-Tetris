#include "Level.h"


Level::Level() 
{
	std::ifstream file;
	std::string input;

	file.open("Levels/level1.txt");
	if (file.fail())
	{
		perror("Levels/level1.txt");
	}

	while (std::getline(file, input))
	{
		m_levelData.push_back(input);
	}

	for (int y = 0; y < m_levelData.size(); y++)
	{
		for (int x = 0; x < m_levelData[y].size(); x++)
		{
			char tile = m_levelData[y][x];

			switch (tile)
			{
			case '#':
				m_levelPosition.push_back(glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH));
				break;
			}
		}
	}
}

Level::~Level()
{
}

void Level::LoadBlocks()
{
	std::ifstream file;
	std::string input;

	file.open("Levels/LShape.txt");
	if (file.fail())
	{
		perror("Levels/LShape.txt");
	}

	while (std::getline(file, input))
	{
		m_LShape.push_back(input);
	}
}
