#include "Block.h"



Block::Block()
{
}


Block::~Block()
{
}

void Block::Init(std::vector <std::string> shape, int type)
{
	m_shape = shape;
	m_type = type;
}

void Block::Draw(glm::vec2 position)
{
	for (int y = 0; y < m_shape.size(); y++)
	{
		for (int x = 0; x < m_shape[y].size(); x++)
		{
			char tile = m_shape[y][x];
			switch (tile)
			{
			case '1':

				break;
			}
		}
	}
}
