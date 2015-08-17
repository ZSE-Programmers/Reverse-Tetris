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