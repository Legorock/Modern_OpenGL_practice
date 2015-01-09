#pragma once

#include <glm/glm.hpp>

namespace sfml_game
{
	namespace rendering_sys
	{
		using namespace glm;

		struct Vertex
		{
			vec3 pos;
			vec2 tex;
			vec3 normal;
		};
	}
}