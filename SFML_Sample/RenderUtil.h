#pragma once

#include <iostream>

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h>

#include <SFML\OpenGL.hpp>

namespace sfml_game
{
	namespace utils
	{
		inline void clearScreen()
		{
			// TODO: Stencil Buffer
			// clear the buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		inline void initGraphics()
		{
			// Initialize GLEW
			glewExperimental = GL_TRUE; // Needed in core profile
			if (glewInit() != GLEW_OK) 
				std::cerr << "Failed to initialize GLEW\n" << std::endl;

			// set the default (clear) value of the color buffer to black
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);

			glFrontFace(GL_CCW);
			glCullFace(GL_BACK);

			// TODO: Depth clamp for later

			//glEnable(GL_FRAMEBUFFER_SRGB); // Creates problems with nvidia drivers (like over-bright rendering)
		}

	}

}