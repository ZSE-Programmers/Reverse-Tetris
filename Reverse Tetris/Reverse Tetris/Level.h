#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <glm/glm.hpp>

#include "Block.h"

class Level
{
public:
    Level();
    ~Level();

    bool InsertBlock(glm::vec2 position, std::vector <std::string>& data, std::vector <Block*>& blocks, bool isInitial, std::list <Shape>& blockTypes);

    Block* FitBlock(glm::vec2& position, std::vector <std::string>& data, std::vector <std::string>& shape);

    void InitNewBlocks(std::vector <Block*>& blocks);

    void InitTutorial(std::string path, std::vector <Block*>& blocks, std::list <Shape>& blockTypes, int part);


    // Getters for level data
    std::vector <std::string>& GetLevelData() { return m_levelData; }
    std::vector <std::string>& GetNewLinesData() { return m_newBlocksData; }
    std::vector <std::string>& GetTutorialData() { return m_tutorialData; }
    std::vector <std::string>& GetTutorialData2() { return m_tutorialData2; }

    //Setters

private:
    // Keep level data in string
    std::vector <std::string> m_levelData;

    std::vector <std::string> m_newBlocksData;

    std::vector <std::string> m_tutorialData;

    std::vector <std::string> m_tutorialData2;

    std::vector <Shape*> m_shapes;

    Shape LShape;
    Shape LShape2;
    Shape LShape3;
    Shape LShape4;

    Shape RLShape;
    Shape RLShape2;
    Shape RLShape3;
    Shape RLShape4;

    Shape ZShape;
    Shape ZShape2;

    Shape RZShape;
    Shape RZShape2;

    Shape SQShape;

    Shape IShape;
    Shape IShape2;

    Shape TShape;
    Shape TShape2;
    Shape TShape3;
    Shape TShape4;
};

