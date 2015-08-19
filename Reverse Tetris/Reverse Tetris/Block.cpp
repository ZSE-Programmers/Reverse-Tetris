#include "Block.h"
#include <fstream>


Block::Block() : m_type(-1)
{
	
}


Block::~Block()
{
}

void Block::AddSquare(int x, int y)
{
	m_position.push_back(glm::vec2(x, y));
}

void Block::AddType(int type)
{
	m_type = type;
}

bool Block::CanRemove(std::vector<std::string>& levelData)
{
	// Counter for squares
	int counter = 0;

	// Looping trough squares positions
	for (int i = 0; i < m_position.size(); i++)
	{
		if (levelData[m_position[i].y - 1][m_position[i].x] == '.')
		{
			counter++;
		}
		else
		{
			// Checking if there is no same block square above it
			for (int j = 0; j < m_position.size(); j++)
			{
				if (m_position[i].y - 1 == m_position[j].y)
				{
					counter++;
				}
			}
		}
	}
	// If all 4 squares are free we can remove
	if (counter == 4)
	{
		return true;
	}
	else
	{
		return false;
	}
}




