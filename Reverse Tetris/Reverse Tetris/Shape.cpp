#include "Shape.h"
#include <fstream>


Shape::Shape()
{
}


Shape::~Shape()
{
}

void Shape::Init(std::string filePath, int type)
{
	std::ifstream file;
	std::string input;

	file.open(filePath);
	if (file.fail())
	{
		perror(filePath.c_str());
	}
	while (std::getline(file, input))
	{
		m_shape.push_back(input);
	}

	m_type = type;
}

