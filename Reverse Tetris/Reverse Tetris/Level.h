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

	void LoadBlocks();

	// Getters for widths
	float GetTileWidth() { return TILE_WIDTH; }
	float GetSquareWidth() { return SQUARE_WIDTH; }
	float GetMiniatureWidth() { return MINIATURE_WIDTH; }

	// Getters for level data
	std::vector <std::string>& GetLevelData() { return m_levelData; }
	
	std::vector <glm::vec2>& GetLevelPosition() { return m_levelPosition; }

	std::vector <std::string>& GetLShape() { return m_LShape; }

	//Setters



private:
	// Keep level data in string
	std::vector <std::string> m_levelData;
	std::vector <std::string> m_figuresShapes;

	// Keep level data position in vec2
	std::vector <glm::vec2> m_levelPosition;

	// L Shape
	std::vector <std::string> m_LShape;

	// Reversed L Shape



	// Blocks widths
	const float TILE_WIDTH = 32.0f;
	const float SQUARE_WIDTH = 28.0f;
	const float MINIATURE_WIDTH = 22.0f;
};

