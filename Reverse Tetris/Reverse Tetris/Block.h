#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Block
{
public:
	Block();
	~Block();

	void AddSquare(int x, int y);
	
	void AddType(int type);

	bool CanRemove(std::vector <std::string>& levelData);

	std::vector <glm::vec2> GetPosition() { return m_position; }

private:
	std::vector <glm::vec2> m_position;
	int m_type;
};

