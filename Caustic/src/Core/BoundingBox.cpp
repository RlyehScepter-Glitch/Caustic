#include "BoundingBox.h"

namespace Caustic
{
	void BoundingBox::SetMin(const glm::vec3& boxMin)
	{
		m_BoxMin = boxMin;
	}

	void BoundingBox::SetMax(const glm::vec3& boxMax)
	{
		m_BoxMax = boxMax;
	}

	const bool BoundingBox::IntersectsBox(const Ray& ray) const
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

	const bool BoundingBox::BoxesIntersection(const BoundingBox& boxA, const BoundingBox& boxB)
	{
		for (uint32_t i = 0; i < 3; i++)
		{
			if(boxA.GetMin()[i] > boxB.GetMax()[i] || boxA.GetMax()[i] < boxB.GetMin()[i])
			{
				return false;
			}
		}
		
		return true;
	}

	const void BoundingBox::Split(uint32_t axisIdx, BoundingBox& boxA, BoundingBox& boxB) const
	{

		float midPoint = (this->GetMax()[axisIdx] - this->GetMin()[axisIdx]) / 2;
		float splitPlaneCoord = this->GetMin()[axisIdx] + midPoint;
		boxA = *this;
		boxB = *this;
		boxA.m_BoxMax[axisIdx] = splitPlaneCoord;
		boxB.m_BoxMin[axisIdx] = splitPlaneCoord;
	}
}