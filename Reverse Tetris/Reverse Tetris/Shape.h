#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Shape
{
public:
	Shape();
	~Shape();

	void Init(std::string filePath);

	std::vector <std::string>& GetShape() { return m_shape; }

private:
	std::vector <std::string> m_shape;
};

