#pragma once

#include "Vec3.h"

#include <cmath>

namespace Caustic
{

	class Ray
	{
	public:
		Ray(const Vec3& origin, const Vec3& direction, float tMin = 0.0f, float tMax = INFINITY, int depth = 0)
		: m_Origin(origin), m_Direction(direction), m_TMin(tMin), m_TMax(tMax), m_Depth(depth)
		{
			
		};

		Vec3 PointAt(float distance) const;

		//Getters
		Vec3 GetOrigin() const;
		Vec3 GetDirection() const;
		float GetTMin() const;
		float GetTMax() const;
		int GetDepth() const;

	private:
		Vec3 m_Origin;
		Vec3 m_Direction;
		float m_TMin;
		float m_TMax;
		int m_Depth;
	};

}