#pragma once

#include "Camera.h"

#define GLM_FORCE_RADIANS
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

namespace sfml_game
{
	class Transform
	{
		typedef rendering_sys::Camera Camera;
	public:
		Transform(const glm::vec3 & pos = glm::vec3(), const glm::vec3 & rotation = glm::vec3(), const glm::vec3 & scale = glm::vec3(1.0, 1.0, 1.0)) :
			m_pos(pos),
			m_rotation(rotation),
			m_scale(scale)
		{}
		
		virtual ~Transform(void) {};

		inline glm::mat4 GetModel() const
		{
			glm::mat4 posMatrix = glm::translate(m_pos);
			glm::mat4 rotXMatrix = glm::rotate(m_rotation.x, glm::vec3(1.0, 0.0, 0.0));
			glm::mat4 rotYMatrix = glm::rotate(m_rotation.y, glm::vec3(0.0, 1.0, 0.0));
			glm::mat4 rotZMatrix = glm::rotate(m_rotation.z, glm::vec3(0.0, 0.0, 1.0));
			glm::mat4 scaleMatrix = glm::scale(m_scale);

			glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

			return posMatrix * rotMatrix * scaleMatrix;
		}

		inline glm::mat4 GetMVP(const Camera & camera) const
		{
			glm::mat4 VP = camera.GetViewProjection();
			glm::mat4 M = GetModel();

			return VP * M;
		}

		inline glm::vec3& GetPos() { return m_pos; }
		inline glm::vec3& GetRotation() { return m_rotation; }
		inline glm::vec3& GetScale() { return m_scale; }

		inline void SetPos(const glm::vec3& pos) { m_pos = pos; }
		inline void SetRotation(const glm::vec3& rotation) { m_rotation = rotation; }
		inline void SetScale(const glm::vec3&  scale) { m_scale = scale; }

	protected:
	private:
		glm::vec3 m_pos;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
	};

}