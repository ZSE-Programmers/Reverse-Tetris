#pragma once
#include <glm/glm.hpp>
class Block
{
public:
	Block();
	~Block();

private:
	glm::vec2 m_position;
	int type;
};

