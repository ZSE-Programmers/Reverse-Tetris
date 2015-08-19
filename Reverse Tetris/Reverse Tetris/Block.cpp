#include "Block.h"
#include <fstream>


Block::Block()
{
	
}


Block::~Block()
{
}

void Block::Add(int x, int y)
{
	m_position.push_back(glm::vec2(x, y));
}




