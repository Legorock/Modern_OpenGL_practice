#pragma once

#include "Transform.h"
#include "custom_typedef.h"

#include <glm\glm.hpp>

namespace sfml_game
{
	namespace rendering_sys
	{
		class Light
		{
		public:
			Light(void)
				:m_lightDirection(glm::vec3(0.0f, 0.0f, 1.0f)), m_lightColour(glm::vec3(1.0f, 1.0f, 1.0f)), m_intensity(1.0f)
			{};

			Light(const glm::vec3& lightDirection, const glm::vec3& lightColour, float lightIntensity)
				:m_lightDirection(lightDirection), m_lightColour(lightColour), m_intensity(lightIntensity)
			{};

			virtual ~Light(void) {};

			glm::vec3 getDirection() const { return m_lightDirection; };
			glm::vec3 getColour() const { return m_lightColour; };
			float getIntensity() const { return m_intensity; };

			void setDirection(const glm::vec3& direction) { m_lightDirection = direction; };
			void setColour(const glm::vec3& colour) { m_lightColour = colour; };
			void setIntensity(float intensity) { m_intensity = intensity; };

		private:
			glm::vec3 m_lightDirection;
			glm::vec3 m_lightColour;
			float m_intensity;
		};
	}
}