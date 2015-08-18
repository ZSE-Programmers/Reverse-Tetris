#include "Block.h"
#include <fstream>


Block::Block()
{
}


Block::~Block()
{
}

void Block::Init(int type, std::string filePath)
{
	m_type = type;

	std::ifstream file;
	std::string input;

	file.open(filePath);
	if (file.fail())
	{
		perror("Levels/LShape.txt");
	}
	while (std::getline(file, input))
	{
		m_shape.push_back(input);
	}
}


