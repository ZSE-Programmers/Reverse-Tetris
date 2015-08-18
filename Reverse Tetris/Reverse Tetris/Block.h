#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Block
{
public:
	Block();
	~Block();

	void Init(int type, std::string filePath);

private:
	std::vector <std::string> m_shape;
	int m_type;
};

