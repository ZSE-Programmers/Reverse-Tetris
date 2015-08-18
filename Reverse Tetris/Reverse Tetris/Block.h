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

	std::vector <std::string>& GetShape() { return m_shape; }

private:
	std::vector <std::string> m_shape;
	int m_type;
};

