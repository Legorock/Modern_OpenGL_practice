#pragma once
#include <iostream>
#include <string>

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h>

#include <SFML\OpenGL.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

#include "RenderUtil.h"
#include "Input.h"
#include "Time.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
//#include "Quaternion.h"
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