#pragma once
#include "Shape.h"
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Block
{
public:
	Block();
	~Block();

	void AddSquare(int x, int y);
	
	void AddShape(Shape shape);

	bool CanRemove(std::vector <std::string>& levelData);

	std::vector <glm::vec2> GetPosition() { return m_position; }

	std::vector <std::string> GetShape() { return m_shape.GetShape(); }

private:
	std::vector <glm::vec2> m_position;
	Shape m_shape;
};

