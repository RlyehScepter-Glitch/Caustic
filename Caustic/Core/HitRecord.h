#pragma once
#include "Vec3.h"

namespace Caustic
{

	struct HitRecord
	{
	public:
		float m_Distance;
		Vec3 m_IntersectionPoint;
		Vec3 m_Normal;

		HitRecord() {}
		HitRecord(float distance, const Vec3& intersectionPoint, const Vec3& normal)
			: m_Distance(distance), m_IntersectionPoint(intersectionPoint), m_Normal(normal) {}
	};

}