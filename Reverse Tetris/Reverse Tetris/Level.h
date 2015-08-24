#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <glm/glm.hpp>

#include "Block.h"

class Level
{
public:
	Level();
	~Level();

	bool InsertBlock(glm::vec2 position, std::vector <std::string>& data, std::vector <Block*>& blocks, glm::vec2 range, std::vector <Shape>& blockTypes);

	Block* FitBlock(glm::vec2& position, std::vector <std::string>& data, std::vector <std::string>& shape);

	void InitNewBlocks(std::vector <Block*>& blocks);


	// Getters for level data
	std::vector <std::string>& GetLevelData() { return m_levelData; }
	std::vector <std::string>& GetNewLinesData() { return m_newBlocksData; }

	//Setters

private:
	// Keep level data in string
	std::vector <std::string> m_levelData;

	std::vector <std::string> m_newBlocksData;


	Shape LShape;
	Shape RLShape;
	Shape ZShape;
	Shape RZShape;
	Shape SQShape;
};

