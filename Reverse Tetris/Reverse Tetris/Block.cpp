#include "Block.h"
#include <fstream>
#include <iostream>

Block::Block() 
{

}

Block::~Block()
{
}

void Block::AddSquare(int x, int y)
{
    m_position.push_back({ x, y });
}

void Block::AddShape(Shape shape)
{
    m_shape = shape;

    std::vector <std::string> type = m_shape.GetShape();
    for (int i = 0; i < type.size(); i++)
    {
        for (int j = 0; j < type[i].size(); j++)
        {
            if (type[i][j] != '.')
            {
                m_type = type[i][j];
                return;
            }
        }
    }
}

bool Block::CanRemove(std::vector<std::string>& levelData)
{
    // Counter for squares
    int counter = 0;

    if (m_position.size() < 4)
    {
        return false;
    }
    else
    {
        // Looping trough squares positions
        for (int i = 0; i < m_position.size(); i++)
        {
            if (levelData[m_position[i].y - 1][m_position[i].x] == '.')
            {
                counter++;
            }
            else
            {
                // Checking if there is no same block square above it
                for (int j = 0; j < m_position.size(); j++)
                {
                    if (m_position[i].y - 1 == m_position[j].y && m_position[i].x == m_position[j].x)
                    {
                        counter++;
                    }
                }
            }
        }
            // If all 4 squares are free we can remove
        if (counter == 4)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void Block::DrawFrame(SDL_Renderer * renderer, SDL_Texture* texture, std::vector <std::string>& levelData)
{
    for (auto const& position : m_position)
    {
        if (position.y < 17)
        {
            // Left side
            if (levelData[position.y][position.x - 1] != m_type)
            {
                SDL_Rect destRect = { position.x * TILE_WIDTH, position.y * TILE_WIDTH, 3, TILE_WIDTH };
                SDL_RenderCopy(renderer, texture, NULL, &destRect);
            }
            else
            {
                if (CheckSide({ position.x - 1, position.y }))
                {
                    SDL_Rect destRect = { position.x * TILE_WIDTH, position.y * TILE_WIDTH, 3, TILE_WIDTH };
                    SDL_RenderCopy(renderer, texture, NULL, &destRect);
                }
            }

            // Right side
            if (levelData[position.y][position.x + 1] != m_type)
            {
                SDL_Rect destRect = { position.x * TILE_WIDTH + TILE_WIDTH, position.y * TILE_WIDTH, 3, TILE_WIDTH };
                SDL_RenderCopy(renderer, texture, NULL, &destRect);
            }
            else
            {
                if (CheckSide({ position.x + 1, position.y }))
                {
                    SDL_Rect destRect = { position.x * TILE_WIDTH + TILE_WIDTH, position.y * TILE_WIDTH, 3, TILE_WIDTH };
                    SDL_RenderCopy(renderer, texture, NULL, &destRect);
                }
            }

            // Upper side
            if (levelData[position.y - 1][position.x] != m_type)
            {
                SDL_Rect destRect = { position.x * TILE_WIDTH, position.y * TILE_WIDTH, TILE_WIDTH, 3 };
                SDL_RenderCopy(renderer, texture, NULL, &destRect);
            }
            else
            {
                if (CheckSide({ position.x, position.y - 1 }))
                {
                    SDL_Rect destRect = { position.x * TILE_WIDTH, position.y * TILE_WIDTH, TILE_WIDTH, 3 };
                    SDL_RenderCopy(renderer, texture, NULL, &destRect);
                }
            }

            // Down side
            if (levelData[position.y + 1][position.x] != m_type)
            {
                SDL_Rect destRect = { position.x * TILE_WIDTH, position.y * TILE_WIDTH + TILE_WIDTH, TILE_WIDTH, 3 };
                SDL_RenderCopy(renderer, texture, NULL, &destRect);
            }
            else
            {
                if (CheckSide({ position.x, position.y + 1 }))
                {
                    SDL_Rect destRect = { position.x * TILE_WIDTH, position.y * TILE_WIDTH + TILE_WIDTH, TILE_WIDTH, 3 };
                    SDL_RenderCopy(renderer, texture, NULL, &destRect);
                }
            }
        }
    }
}

bool Block::CheckSide(glm::ivec2 position)
{
    for (auto const& pos : m_position)
    {
        if (position.x == pos.x && position.y == pos.y)
        {
            return false;
        }
    }
    return true;
}

void Block::SetPosition(std::vector<glm::ivec2> position)
{
    m_position = position;
}




