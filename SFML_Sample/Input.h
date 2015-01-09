#pragma once

#include <SFML\Window.hpp>
#include "custom_typedef.h"

namespace sfml_game
{
	class Input
	{
	public:

		Input(const sf::Window& window_ref);
		virtual ~Input(void);

		bool getKey(int32 keyCode);
		bool getKeyDown(int32 keyCode);
		bool getKeyUp(int32 keyCode);

		bool getMouse(int32 mouseButton);
		bool getMouseDown(int32 mouseButton);
		bool getMouseUp(int32 mouseButton);
		sf::Vector2i getMousePosition();
		void setMousePosition(sf::Vector2i pos);

		void setCursor(bool enabled); // TODO: Implement

	private:
		Input(void); // default constructor disabled

		void update();
		void updateKeys();
		void updateMouse();

	public:
		const static uint32 s_numKeycodes = sf::Keyboard::KeyCount;
		const static uint32 s_numMouseButtons = sf::Mouse::ButtonCount;

	private:
		bool m_lastKeys[s_numKeycodes];
		bool m_lastButtons[s_numMouseButtons];

		const sf::Window& m_window_ref;

		friend class SFMLGame;
	};
}