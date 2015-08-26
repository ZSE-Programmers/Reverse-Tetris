#pragma once
#include "Shape.h"
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <SDL/SDL.h>

class Block
{
public:
    Block();
    ~Block();

    void AddSquare(int x, int y);
	
    void AddShape(Shape shape);

    bool CanRemove(std::vector <std::string>& levelData);
    
    void DrawFrame(SDL_Renderer* renderer, SDL_Texture* texture, std::vector <std::string>& levelData);

    bool CheckSide(glm::ivec2 position);

    std::vector <glm::ivec2> GetPosition() { return m_position; }

    Shape& GetShape() { return m_shape; }



    void SetPosition(std::vector <glm::ivec2> position);

private:
    std::vector <glm::ivec2> m_position;
    std::vector <SDL_Rect> m_framePosition;
    Shape m_shape;

    char m_type;

    int TILE_WIDTH = 32;
};

