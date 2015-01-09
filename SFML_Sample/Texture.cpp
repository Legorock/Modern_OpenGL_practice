#include "Texture.h"


#include <SFML\Graphics\Image.hpp>
#include <iostream>
#include "custom_typedef.h"

namespace sfml_game
{
	namespace rendering_sys
	{
		Texture::Texture(const std::string & fileName)
		{
			uint32 _width, _height;

			sf::Image _tex;
			if(!_tex.loadFromFile(fileName))
				std::cerr << "Unable to load file : " << fileName << std::endl;

			sf::Vector2u _texDim = _tex.getSize();
			_width = _texDim.x;
			_height = _texDim.y;
			const unsigned char* _data = static_cast<const unsigned char*>(_tex.getPixelsPtr()); 

			if(_data == NULL)
				std::cerr << "Unable to load texture : " << fileName << std::endl;

			glGenTextures(1, &m_texture);
			glBindTexture(GL_TEXTURE_2D, m_texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);
		}

		Texture::~Texture(void)
		{
			glDeleteTextures(1, &m_texture);
		}


		void Texture::Bind()
		{
			glBindTexture(GL_TEXTURE_2D, m_texture);
		}

	}
}