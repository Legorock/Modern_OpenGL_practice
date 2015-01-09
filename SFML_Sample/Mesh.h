#pragma once

#include <GL/glew.h> // always include before opengl
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "custom_typedef.h"
#include "Vertex.h"
#include "obj_loader.h"

namespace sfml_game
{
	namespace rendering_sys
	{
		using namespace glm;

		class Mesh
		{

		public:
			Mesh(Vertex * const vertices, uint32 numVertices, uint32 * indices, uint32 numIndices);
			Mesh(const std::string & fileName);
			virtual ~Mesh(void);

			void Draw();

		private:
			enum
			{
				POSITION_VB, // position vertex buffer index
				TEXCOORD_VB, // texture vertex buffer index
				NORMAL_VB,	// normal vertex buffer index

				INDEX_VB, 

				NUM_BUFFERS			
			};

			GLuint m_vao; // vertex array object
			GLuint m_vab[NUM_BUFFERS]; // vertex array buffers
			
			uint32 m_drawCount;

		private:
			void InitMesh(const IndexedModel & model);

			Mesh(const Mesh& mesh);
			void operator=(const Mesh& mesh);
		};

	}
}