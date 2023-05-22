#include "Ray.h"

namespace Caustic
{
	glm::vec3 Ray::PointAt(float distance) const
	{
		return m_Origin + m_Direction * distance;
	}
	
	void Ray::SetOrigin(const glm::vec3& origin)
	{
		m_Origin = origin;
	}

	void Ray::SetDirection(const glm::vec3& direction)
	{
		m_Direction = direction;
	}
}