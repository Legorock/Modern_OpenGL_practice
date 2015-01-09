#pragma once
#include <string>
#include <SFML\Window.hpp>
#include "Input.h"
#include "custom_typedef.h"

namespace sfml_game
{
	class Input;
	class SFMLGame
	{
	public:
		SFMLGame(void);
		SFMLGame(std::string title, uint32 height, uint32 width, uint32 style, sf::ContextSettings& contextSettings);
		virtual ~SFMLGame(void);

		void start();
		void stop();
		void pause();
		void resume();
		void restart();		

	protected:
		virtual void init() = 0;
		virtual void dispose() = 0;

		virtual void render() = 0;
		virtual void update(sf::Time deltaTime) = 0;

	protected:
		sf::Window m_window;
		Input m_input;

	private:
		void run();
		void processEvents();

	private:	
		game_state m_state;
		
	};
}