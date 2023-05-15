#pragma once

#include <glm/glm.hpp>

#include <cmath>

namespace Caustic
{

	class Ray
	{
	public:
		Ray(const glm::vec3& origin, const glm::vec3& direction, float tMin = 0.0f, float tMax = INFINITY, int depth = 0)
		: m_Origin(origin), m_Direction(direction), m_TMin(tMin), m_TMax(tMax), m_Depth(depth)
		{
			
		};

		glm::vec3 PointAt(float distance) const;

		//Getters
		glm::vec3 GetOrigin() const;
		glm::vec3 GetDirection() const;
		float GetTMin() const;
		float GetTMax() const;
		int GetDepth() const;
	private:
		glm::vec3 m_Origin;
		glm::vec3 m_Direction;
		float m_TMin;
		float m_TMax;
		int m_Depth;
	};

}