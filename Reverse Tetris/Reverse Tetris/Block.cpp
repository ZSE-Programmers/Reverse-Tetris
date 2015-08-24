#include "Block.h"
#include <fstream>


Block::Block() 
{
	
}


Block::~Block()
{
}

void Block::AddSquare(int x, int y)
{
	m_position.push_back(glm::vec2(x, y));
}

void Block::AddShape(Shape shape)
{
	m_shape = shape;
}

bool Block::CanRemove(std::vector<std::string>& levelData)
{
	// Counter for squares
	int counter = 0;

	if (m_position.size() < 4)
	{
		return false;
	}
	else
	{
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
					if (m_position[i].y - 1 == m_position[j].y && m_position[i].x == m_position[j].x)
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
}

void Block::SetPosition(std::vector<glm::vec2> position)
{
	m_position = position;
}




