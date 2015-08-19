#pragma once
#include <unordered_map>
#include <glm/glm.hpp>
class InputManager
{
public:
	InputManager();
	~InputManager();

	void PressKey(unsigned int keyID);
	void ReleaseKey(unsigned int keyID);
	bool IsKeyPressed(unsigned int keyID);

	void PressButton();
	void ReleaseButton();
	bool IsButtonPressed();

	void SetMousePosition(glm::vec2 mousePosition);
	glm::vec2 GetMousePosition() { return m_mousePosition; }
private:
	bool m_button;
	std::unordered_map <unsigned int, bool> m_keyMap;
	glm::vec2 m_mousePosition;
};

