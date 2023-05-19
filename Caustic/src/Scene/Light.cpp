#include "Light.h"

namespace Caustic 
{
	Light::Light(uint32_t intensity, const glm::vec3& position)
		:m_Intensity(intensity), m_Position(position)
	{
	}
	
	void Light::SetIntensity(uint32_t intensity)
	{
		m_Intensity = intensity;
	}

	void Light::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
	}

	void Light::MoveLight(const glm::vec3& direction)
	{
		m_Position += direction;
	}
}