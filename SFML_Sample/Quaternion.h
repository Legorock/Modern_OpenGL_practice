#pragma once

#include <math.h>

#define GLM_FORCE_RADIANS
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#include "custom_typedef.h"

namespace sfml_game
{

	class Quaternion // Incomplete
	{
	public:
		Quaternion(const glm::vec4 & quaternion = glm::vec4())
			:m_q(quaternion)
		{}

		virtual ~Quaternion(void)
		{}

		inline float magnitude() const 
		{ 
			return sqrtf(powf(m_q.w,2) + powf(m_q.x,2) + powf(m_q.y,2) + powf(m_q.z,2));
		}

		inline void norm()
		{
			float magnitude = static_cast<const Quaternion *>(this)->magnitude();

			m_q.w /= magnitude;
			m_q.x /= magnitude;
			m_q.y /= magnitude;
			m_q.z /= magnitude;
		}

		inline Quaternion newNorm() const
		{
			Quaternion newQ(m_q);
			newQ.norm();
			return newQ;
		}

		inline void conjugate()
		{
			m_q.x = -m_q.x;
			m_q.y = -m_q.y;
			m_q.z = -m_q.z;
		}

		inline Quaternion newConjuagate() const
		{
			Quaternion newQ(m_q);
			newQ.conjugate();
			return newQ;
		}

		Quaternion& operator*=(const Quaternion& rhs) 
		{
			float w = m_q.w * rhs.m_q.w - m_q.x * rhs.m_q.x - m_q.y * rhs.m_q.y - m_q.z * rhs.m_q.z;
			float x = m_q.x * rhs.m_q.w + m_q.w * rhs.m_q.x + m_q.y * rhs.m_q.z - m_q.z * rhs.m_q.y;
			float y = m_q.y * rhs.m_q.w + m_q.w * rhs.m_q.y + m_q.z * rhs.m_q.x - m_q.x * rhs.m_q.z;
			float z = m_q.z * rhs.m_q.z + m_q.w * rhs.m_q.z + m_q.x * rhs.m_q.y - m_q.y * rhs.m_q.x;

			m_q.w = w;
			m_q.x = x;
			m_q.y = y;
			m_q.z = z;
			
			return *this;
		}


	private:
		glm::vec4 m_q;
	};

	inline Quaternion operator*(Quaternion lhs, const Quaternion& rhs)
	{
		return lhs *= rhs;
	}

}