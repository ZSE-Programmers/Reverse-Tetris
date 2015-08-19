#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Block
{
public:
	Block();
	~Block();

	void Add(int x, int y);

	std::vector <glm::vec2> GetPosition() { return m_position; }

private:
	std::vector <glm::vec2> m_position;
};

