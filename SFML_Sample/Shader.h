#pragma once

#include <string>
#include <GL/glew.h>
#include <fstream>

#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "custom_typedef.h"

namespace sfml_game
{
	namespace rendering_sys
	{
		class Shader
		{
		public:
			Shader(const std::string & fileName);
			virtual ~Shader(void);

			void Bind();
			void Update(const Transform & transform, const Camera & camera, const Light & light);

		protected:

		private:
			static const uint32 NUM_SHADERS = 2;

			void operator=(const Shader& shader) {}
			Shader(const Shader& shader) {}

			std::string LoadShader(const std::string & fileName);
			void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage);
			GLuint CreateShader(const std::string & text, unsigned int type);

			void UpdateLight(const Light& light);

			enum 
			{
				TRANSFORM_U,

				LIGHTDIR_U,			// Light Direction (vec3)
				LIGHTCOLOUR_U,		// Light Colour (vec3)
				LIGHTINTENSITY_U,	// Light Intensity (float)

				NUM_UNIFORMS
			};

			GLuint m_program;
			GLuint m_shaders[NUM_SHADERS];
			GLuint m_uniforms[NUM_UNIFORMS];
		};
	}
}