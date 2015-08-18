#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Block
{
public:
	Block();
	~Block();

	void Init(std::vector <std::string> shape, int type);
	void Draw(glm::vec2 position);

private:
	std::vector <std::string> m_shape;
	int m_type;
};

