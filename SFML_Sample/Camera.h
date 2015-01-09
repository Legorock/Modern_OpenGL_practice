#pragma once

#define GLM_FORCE_RADIANS
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

namespace sfml_game
{
	namespace rendering_sys
	{
		class Camera
		{
		public:

			Camera(const glm::vec3 & pos, float fov, float aspect, float zNear, float zFar) 
				:
				m_perspective(glm::perspective(glm::radians(fov), aspect, zNear, zFar)),
				m_position(pos),
				m_forward(glm::vec3(0.0, 0.0, 1.0)),
				m_up(glm::vec3(0.0, 1.0, 0.0))
			{}

			virtual ~Camera(void) {}

			inline glm::mat4 GetViewProjection() const
			{
				return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
			}


			inline glm::vec3&  GetPosition() { return m_position; }
			
			inline void SetPosition(const glm::vec3 & pos) { m_position = pos; } 

		protected:
		private:
			glm::mat4 m_perspective;
			glm::vec3 m_position;
			glm::vec3 m_forward;
			glm::vec3 m_up;
		};
	}
}