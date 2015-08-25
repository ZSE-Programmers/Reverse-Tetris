#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Shape
{
public:
    Shape();
    ~Shape();

    void Init(std::string filePath, int type);

    // Getters
    std::vector <std::string>& GetShape() { return m_shape; }
    glm::vec2& GetPosition() { return m_position; }

    // Setters
    void SetPosition(glm::vec2 position);

private:
    std::vector <std::string> m_shape;
    int m_type;
    glm::vec2 m_position;
};

