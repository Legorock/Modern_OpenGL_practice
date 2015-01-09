#pragma once

#include <string>
#include <GL\glew.h>

namespace sfml_game
{
	namespace rendering_sys
	{
		class Texture
		{
		public:
			Texture(const std::string & fileName);
			virtual ~Texture(void);

			void Bind();

		protected:
		private:
			Texture(const Texture & texture) {}
			void operator=(const Texture & texture) {}

			GLuint m_texture;
		};
	}
}