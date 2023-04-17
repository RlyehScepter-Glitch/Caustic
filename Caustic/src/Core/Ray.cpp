#include "Ray.h"

namespace Caustic
{
	glm::vec3 Ray::PointAt(float distance) const
	{
		return m_Origin + m_Direction * distance;
	}
	
	glm::vec3 Ray::GetOrigin() const
	{
		return m_Origin;
	}
	
	glm::vec3 Ray::GetDirection() const
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