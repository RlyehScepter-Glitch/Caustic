#include "BoundingBox.h"

namespace Caustic
{
	bool BoundingBox::IntersectsBox(const Ray& ray)
	{
		float tmin = (m_BoxMin.x - ray.GetOrigin().x) / ray.GetDirection().x;
		float tmax = (m_BoxMax.x - ray.GetOrigin().x) / ray.GetDirection().x;

		if (tmin > tmax)
			std::swap(tmin, tmax);

		float tymin = (m_BoxMin.y - ray.GetOrigin().y) / ray.GetDirection().y;
		float tymax = (m_BoxMax.y - ray.GetOrigin().y) / ray.GetDirection().y;

		if (tymin > tymax)
			std::swap(tymin, tymax);

		if ((tmin > tymax) || (tymin > tmax))
			return false;

		if (tymin > tmin)
			tmin = tymin;

		if (tymax < tmax)
			tmax = tymax;

		float tzmin = (m_BoxMin.z - ray.GetOrigin().z) / ray.GetDirection().z;
		float tzmax = (m_BoxMax.z - ray.GetOrigin().z) / ray.GetDirection().z;

		if (tzmin > tzmax)
			std::swap(tzmin, tzmax);

		if ((tmin > tzmax) || (tzmin > tmax))
			return false;

		return true;
	}
}