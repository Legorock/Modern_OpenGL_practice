#pragma once
#include <iostream>
#include <SFML\System.hpp>

namespace sfml_game
{
	class Time
	{

	public:

		Time(void) :m_frameClock(), m_frameRateDispClock(), m_deltaTime(), m_frameRateDispElapsed() {}

		~Time(void){}

		sf::Time getDeltaTime()
		{
			update();
			return 	m_deltaTime;
		}

	protected:
		void update()
		{
			m_deltaTime = m_frameClock.restart();
			m_frameRateDispElapsed = m_frameRateDispClock.getElapsedTime();
			if(m_frameRateDispElapsed.asMilliseconds() > s_milisecsInSec)
			{				
				std::cout << "FPS: " << s_microsecsInSec/m_deltaTime.asMicroseconds() << std::endl;
				m_frameRateDispClock.restart();
			}
		}

	private:	
		const static long s_microsecsInSec = 1000000;
		const static long s_milisecsInSec = 1000;

	private:
		sf::Time m_deltaTime;
		sf::Time m_frameRateDispElapsed;

		sf::Clock m_frameClock;
		sf::Clock m_frameRateDispClock;
	};

}