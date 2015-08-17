#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <glm/glm.hpp>

class Level
{
public:
	Level();
	~Level();

	// Getters
	std::vector <std::string>& GetLevelData() { return m_levelData; }
	
	std::vector <glm::vec2>& GetLevelPosition() { return m_levelPosition; }

	//Setters



private:
	// Keep level data in string
	std::vector <std::string> m_levelData;

	// Keep level data position in vec2
	std::vector <glm::vec2> m_levelPosition;

	float TILE_WIDTH;
};

