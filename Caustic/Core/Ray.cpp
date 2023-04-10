#include "Ray.h"

namespace Caustic
{
	Vec3 Ray::PointAt(float distance) const
	{
		return m_Origin + m_Direction * distance;
	}
	
	Vec3 Ray::GetOrigin() const
	{
		return m_Origin;
	}
	
	Vec3 Ray::GetDirection() const
	{
		return m_Direction;
	}
	
	float Ray::GetTMin() const
	{
		return m_TMin;
	}
	
	float Ray::GetTMax() const
	{
		return m_TMax;
	}
	
	int Ray::GetDepth() const
	{
		return m_Depth;
	}
}