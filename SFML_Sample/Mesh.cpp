#include "Mesh.h"

//#include "obj_loader.h"
//#include <vector>

namespace sfml_game
{
	namespace rendering_sys
	{
		using namespace glm;

		Mesh::Mesh(const std::string & fileName)
		{
			IndexedModel model = OBJModel(fileName).ToIndexedModel();
			InitMesh(model);
		}

		Mesh::Mesh(Vertex * const vertices, uint32 numVertices, uint32 * indices, uint32 numIndices)
		{
			IndexedModel model;

			for(uint32 i = 0; i < numVertices; i++)
			{
				model.positions.push_back(vertices[i].pos);
				model.texCoords.push_back(vertices[i].tex);
				model.normals.push_back(vertices[i].normal);
			}

			for(uint32 i = 0; i < numIndices; i++)
			{
				model.indices.push_back(indices[i]);
			}

			InitMesh(model);
		}

		Mesh::~Mesh(void) 
		{
			glDeleteBuffers(NUM_BUFFERS, m_vab);
			glDeleteVertexArrays(1, &m_vao);
		}

		void Mesh::InitMesh(const IndexedModel & model)
		{
			m_drawCount = model.indices.size();

			glGenVertexArrays(1, &m_vao);
			glBindVertexArray(m_vao);

			// Generates Buffer on GPU, 
			glGenBuffers(NUM_BUFFERS, m_vab);

			glBindBuffer(GL_ARRAY_BUFFER, m_vab[POSITION_VB]);	// Binds buffer to m_vab, 
			glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);	// copies data to GPU as static data.
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 	// Vertex attribute for position

			glBindBuffer(GL_ARRAY_BUFFER, m_vab[TEXCOORD_VB]);	// Binds buffer to m_vab,
			glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);	// copies data to GPU as static data.
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);	// Vertex attribute for texture coordinates

			glBindBuffer(GL_ARRAY_BUFFER, m_vab[NORMAL_VB]);	// Binds buffer to m_vab, 
			glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);	// copies data to GPU as static data.
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0); 	// Vertex attribute for position

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vab[INDEX_VB]);	// Binds buffer to m_vab,
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);	// copies data to GPU as static data.

			glBindVertexArray(0);			
		}

		void Mesh::Draw()
		{
			glBindVertexArray(m_vao);

			// Draw vertex as triangles
			glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
			//glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

			glBindVertexArray(0);
		}
	}
}