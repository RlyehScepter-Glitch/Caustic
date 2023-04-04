#pragma once

#include "Vec3.h"
#include "Ray.h"
#include "HitRecord.h"

namespace Caustic
{

	class Triangle
	{
	public:
		Triangle() {}
		Triangle(const Vec3& v1, const Vec3& v2, const Vec3& v3)
			: m_V1(v1), m_V2(v2), m_V3(v3) 
		{
			m_Normal = Vec3::Cross(v2 - v1, v3 - v1);
			m_Normal.Normalize();
		}

		bool Intersect(const Ray& ray, HitRecord& hitRecord) const;


	private:
		Vec3 m_V1, m_V2, m_V3;
		Vec3 m_Normal;
	};

}