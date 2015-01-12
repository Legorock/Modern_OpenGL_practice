#include <iostream>
#include <SFML\OpenGL.hpp>
#include <SFML\System.hpp>
#include "SFMLGame.h"
#include "Time.h"

namespace sfml_game
{
	SFMLGame::SFMLGame(void)
		: m_window(sf::VideoMode(800, 600), "OpenGL Game", sf::Style::Default, sf::ContextSettings(32,0,0,3,0)), m_input(m_window)
	{
		m_window.setFramerateLimit(0);
		m_state = game_state::Stopped;
	}

	SFMLGame::SFMLGame(std::string title, uint32 height, uint32 width, uint32 style = sf::Style::Default, sf::ContextSettings& contextSettings = sf::ContextSettings(32,0,0,3,0))
		: m_window(sf::VideoMode(height, width), title, style, contextSettings), m_input(m_window)
	{
		m_window.setFramerateLimit(0);
		m_state = game_state::Stopped;
	}
	 
	SFMLGame::~SFMLGame(void) {}

	void SFMLGame::start()
	{
		if(m_state == game_state::Stopped)
		{
			init();
			m_state = game_state::Running;

			run();
		}
	}

	void SFMLGame::stop()
	{
		if(m_state != game_state::Stopped)
		{
			dispose();
			m_state = game_state::Stopped;
		}
	}

	void SFMLGame::pause()
	{
		if(m_state != game_state::Stopped)
		{
			m_state = game_state::Paused;
		}
	}

	void SFMLGame::resume()
	{
		if(m_state == game_state::Paused)
		{
			m_state = game_state::Running;
		}
	}

	// TODO: Check if working correctly
	void SFMLGame::restart()
	{
		std::cout << "Game Restart" << std::endl;
		init();
	}

	void SFMLGame::run()
	{
		// Constant frame time for physics and simulation updates
		const static sf::Time _TimePerFrame = sf::seconds(1.f / 60.f);

		// Mainloop of the game paused game
		while(m_state != game_state::Stopped)
		{
			processEvents();

			sf::Time _timeSinceLastUpdate = sf::Time::Zero;

			// Mainloop of the game running game
			while(m_state == game_state::Running)
			{
				static Time _t;
				sf::Time _deltaTime = _t.getDeltaTime();

				//processEvents();
				 
				_timeSinceLastUpdate += _deltaTime;
				while(_timeSinceLastUpdate > _TimePerFrame)
				{
					_timeSinceLastUpdate -= _TimePerFrame;

					update(_TimePerFrame);
					m_input.update();
				}

				render();

				m_window.display();

				processEvents();
			} // Mainloop(running)

			// sleep 100 ms when this game_state paused
			sf::sleep(sf::milliseconds(100));
		} // Mainloop(paused)
	}

	void SFMLGame::processEvents()
	{
		// handle events
		sf::Event _event;
		while (m_window.pollEvent(_event))
		{
			switch(_event.type)
			{
			case sf::Event::GainedFocus:
				// resume the game loop
				resume();
				break;
			case sf::Event::LostFocus:
				// pause the game loop
				pause();
				break;
			case sf::Event::Closed:
				// end the program
				stop();
				break;
			case sf::Event::Resized:
				// adjust the viewport when the window is resized
				glViewport(0, 0, _event.size.width, _event.size.height);
				break;
			default: break;
			}
		}		
	}

}