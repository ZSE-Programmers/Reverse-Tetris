#include "Shape.h"
#include <fstream>


Shape::Shape()
{
}


Shape::~Shape()
{
}

void Shape::Init(int type, std::string filePath)
{
	m_type = type;

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
}


