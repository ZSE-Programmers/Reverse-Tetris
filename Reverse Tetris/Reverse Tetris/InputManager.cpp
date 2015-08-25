#include "InputManager.h"


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::PressKey(unsigned int keyID)
{
    m_keyMap[keyID] = true;
}

void InputManager::ReleaseKey(unsigned int keyID)
{
    m_keyMap[keyID] = false;
}

bool InputManager::IsKeyPressed(unsigned int keyID)
{
    auto it = m_keyMap.find(keyID);
    if (it != m_keyMap.end())
    {
        return it->second;
    }
    else
    {
        return false;
    }
}

void InputManager::PressButton()
{
    m_button = true;
}

void InputManager::ReleaseButton()
{
    m_button = false;
}

bool InputManager::IsButtonPressed()
{
    if (m_button)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void InputManager::SetMousePosition(glm::vec2 mousePosition)
{
    m_mousePosition = mousePosition;
}
