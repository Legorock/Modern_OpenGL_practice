#pragma once
#include <SFML\OpenGL.hpp>

namespace sfml_game
{
	namespace utils
	{
		void clearScreen()
		{
			// TODO: Stencil Buffer
			// clear the buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void initGraphics()
		{
			// set the default (clear) value of the color buffer to black
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);

			glFrontFace(GL_CCW);
			glCullFace(GL_BACK);

			// TODO: Depth clamp for later

			glEnable(GL_FRAMEBUFFER_SRGB);
		}

	}

}