#include "Level.h"
#include <random>
#include <ctime>

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

	// Initalizing shapes
	LShape.Init("Levels/LShape.txt", 1);
	RLShape.Init("Levels/RLShape.txt", 2);
	ZShape.Init("Levels/ZShape.txt", 3);
	RZShape.Init("Levels/RZShape.txt", 4);
	SQShape.Init("Levels/SQShape.txt", 5);
}

Level::~Level()
{
}


bool Level::InsertBlock(glm::vec2 position, std::vector<std::string>& data, std::vector<Block*>& blocks, glm::vec2 range, std::vector <Shape>& blockTypes)
{
	static std::mt19937 randomEngine(time(NULL));
	std::uniform_int_distribution <int> roll(range.x, range.y);

	int newRoll = roll(randomEngine);
	std::vector <std::string> strShape;

	Block* tmp_block = nullptr;

	switch (newRoll)
	{
	case 1:
		if (tmp_block = FitBlock(position, data, LShape.GetShape()))
		{
			blockTypes.push_back(LShape);
			tmp_block->AddShape(LShape);
			blocks.push_back(tmp_block);
			return true;
		}
		break;
	case 2:
		if (tmp_block = FitBlock(position, data, RLShape.GetShape()))
		{
			blockTypes.push_back(RLShape);
			tmp_block->AddShape(RLShape);
			blocks.push_back(tmp_block);
			return true;
		}
		break;
	case 3:
		if (tmp_block = FitBlock(position, data, ZShape.GetShape()))
		{
			blockTypes.push_back(ZShape);
			tmp_block->AddShape(ZShape);
			blocks.push_back(tmp_block);
			return true;
		}
		break;
	case 4:
		if (tmp_block = FitBlock(position, data, RZShape.GetShape()))
		{
			blockTypes.push_back(RZShape);
			tmp_block->AddShape(RZShape);
			blocks.push_back(tmp_block);
			return true;
		}
		break;
	case 5:
		strShape = SQShape.GetShape();
		if (tmp_block = FitBlock(position, data, SQShape.GetShape()))
		{
			blockTypes.push_back(SQShape);
			tmp_block->AddShape(SQShape);
			blocks.push_back(tmp_block);
			return true;
		}
		break;
	}
	return false;
}

Block* Level::FitBlock(glm::vec2 & position, std::vector<std::string>& data, std::vector<std::string>& shape)
{
	int counter = 0;
	// Check all tiles from shape 
	for (int y = 0; y < shape.size(); y++)
	{
		for (int x = 0; x < shape[y].size(); x++)
		{
			char tile = shape[y][x];
			if (tile != '.')
			{
				if (data[position.y + y][position.x + x] == '.')
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
		for (int y = 0; y < shape.size(); y++)
		{
			for (int x = 0; x < shape[y].size(); x++)
			{
				tile = shape[y][x];
				if (tile != '.')
				{
					data[position.y + y][position.x + x] =  tile;
					tmp_block->AddSquare(position.x + x, position.y + y);
				}
			}
		}
		return tmp_block;
	}
	return nullptr;
}

void Level::InitNewBlocks(std::vector <Block*>& blocks)
{
	std::ifstream file;
	std::string input;
	file.open("Levels/newlanes.txt");
	if (file.fail())
	{
		perror("Levels/newlanes.txt");
		return;
	}
	while (std::getline(file, input))
	{
		m_newBlocksData.push_back(input);
	}
}



