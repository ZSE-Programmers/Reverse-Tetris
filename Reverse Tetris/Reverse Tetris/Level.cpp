#include "Level.h"
#include <random>
#include <ctime>

Level::Level() 
{
    std::ifstream file;
    std::string input;

    file.open("Levels/level1.txt");
    if (file.fail())
    {
        perror("Levels/level1.txt");
    }

    while (std::getline(file, input))
    {
        m_levelData.push_back(input);
    }

    // Initalizing shapes
    LShape.Init("Shapes/LShape.txt", 1);
    m_shapes.push_back(&LShape);
    LShape2.Init("Shapes/LShape2.txt", 1);
    m_shapes.push_back(&LShape2);
    LShape3.Init("Shapes/LShape3.txt", 1);
    m_shapes.push_back(&LShape3);
    LShape4.Init("Shapes/LShape4.txt", 1);
    m_shapes.push_back(&LShape4);

    RLShape.Init("Shapes/RLShape.txt", 2);
    m_shapes.push_back(&RLShape);
    RLShape2.Init("Shapes/RLShape2.txt", 2);
    m_shapes.push_back(&RLShape2);
    RLShape3.Init("Shapes/RLShape3.txt", 2);
    m_shapes.push_back(&RLShape3);
    RLShape4.Init("Shapes/RLShape4.txt", 2);
    m_shapes.push_back(&RLShape4);

    ZShape.Init("Shapes/ZShape.txt", 3);
    m_shapes.push_back(&ZShape);
    ZShape2.Init("Shapes/ZShape2.txt", 3);
    m_shapes.push_back(&ZShape2);

    RZShape.Init("Shapes/RZShape.txt", 4);
    m_shapes.push_back(&RZShape);
    RZShape2.Init("Shapes/RZShape2.txt", 4);
    m_shapes.push_back(&RZShape2);

    SQShape.Init("Shapes/SQShape.txt", 5);
    m_shapes.push_back(&SQShape);

    IShape.Init("Shapes/IShape.txt", 6);
    m_shapes.push_back(&IShape);
    IShape2.Init("Shapes/IShape2.txt", 6);
    m_shapes.push_back(&IShape2);

    TShape.Init("Shapes/TShape.txt", 7);
    m_shapes.push_back(&TShape);
    TShape2.Init("Shapes/TShape2.txt", 7);
    m_shapes.push_back(&TShape2);
    TShape3.Init("Shapes/TShape3.txt", 7);
    m_shapes.push_back(&TShape3);
    TShape4.Init("Shapes/TShape4.txt", 7);
    m_shapes.push_back(&TShape4);
}

Level::~Level()
{
}


bool Level::InsertBlock(glm::vec2 position, std::vector<std::string>& data, std::vector<Block*>& blocks, bool isInitial, std::vector <Shape>& blockTypes)
{
    static std::mt19937 randomEngine(time(NULL));
    std::uniform_int_distribution <int> roll(0, m_shapes.size() - 1);

    int newRoll = roll(randomEngine);

    if (isInitial)
    {
        while (m_shapes[newRoll]->GetType() != 3 && m_shapes[newRoll]->GetType() != 4)
        {
            newRoll = roll(randomEngine);
        }
    }

    Block* tmp_block = nullptr;

    if (tmp_block = FitBlock(position, data, m_shapes[newRoll]->GetShape()))
    {
        blockTypes.push_back(*m_shapes[newRoll]);
        tmp_block->AddShape(*m_shapes[newRoll]);
        blocks.push_back(tmp_block);
        return true;
    }
    return false;
}

Block* Level::FitBlock(glm::vec2 & position, std::vector<std::string>& data, std::vector<std::string>& shape)
{
    int counter = 0;
    // Check all tiles from shape 
    for (int y = 0; y < shape.size(); y++)
    {
        for (int x = 0; x < shape[y].size(); x++)
        {
            char tile = shape[y][x];
            if (tile != '.')
            {
                if (data[position.y + y][position.x + x] == '.')
                {
                    counter++;
                }
            }
        }
    }
        // If all 4 tiles are empty we can draw our block
        if (counter == 4)
        {
            char tile;
            Block* tmp_block = new Block;
            for (int y = 0; y < shape.size(); y++)
            {
                for (int x = 0; x < shape[y].size(); x++)
                {
                    tile = shape[y][x];
                    if (tile != '.')
                    {
                        data[position.y + y][position.x + x] =  tile;
                        tmp_block->AddSquare(position.x + x, position.y + y);
                    }
                }
            }
        return tmp_block;
    }
    return nullptr;
}

void Level::InitNewBlocks(std::vector <Block*>& blocks)
{
    std::ifstream file;
    std::string input;
    file.open("Levels/newlanes.txt");
    if (file.fail())
    {
        perror("Levels/newlanes.txt");
        return;
    }
    while (std::getline(file, input))
    {
        m_newBlocksData.push_back(input);
    }
}



