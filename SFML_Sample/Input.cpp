#include "Input.h"
#include <iostream>

namespace sfml_game
{
	Input::Input(const sf::Window& window_ref) : m_window_ref(window_ref)
	{
		for(int32 i = 0; i < s_numKeycodes; ++i)
			m_lastKeys[i] = false;

		for(int32 i = 0; i < s_numMouseButtons; ++i)
			m_lastButtons[i] = false;		
	}
	Input::~Input(void) {}

	void Input::update()
	{
		updateKeys();
		updateMouse();
	}

	void Input::updateKeys()
	{
		for(int32 i = 0; i < s_numKeycodes; ++i)
			m_lastKeys[i] = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));
	}

	void Input::updateMouse()
	{
		for(int32 i = 0; i < s_numMouseButtons; ++i)
			m_lastButtons[i] = sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(i));
	}

	bool Input::getKey(int32 keyCode)
	{
		return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keyCode));
	}

	bool Input::getKeyDown(int32 keyCode)
	{
		return getKey(keyCode) && !m_lastKeys[keyCode];
	}

	bool Input::getKeyUp(int32 keyCode)
	{
		return !getKey(keyCode) && m_lastKeys[keyCode];
	}

	bool Input::getMouse(int32 mouseButton)
	{
		return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(mouseButton));
	}

	bool Input::getMouseDown(int32 mouseButton)
	{
		return getMouse(mouseButton) && !m_lastButtons[mouseButton];
	}

	bool Input::getMouseUp(int32 mouseButton)
	{
		return !getMouse(mouseButton) && m_lastButtons[mouseButton];
	}

	sf::Vector2i Input::getMousePosition()
	{
		return sf::Mouse::getPosition(m_window_ref);
	}

	void Input::setMousePosition(sf::Vector2i pos)
	{
		sf::Mouse::setPosition(pos, m_window_ref);
	}
}