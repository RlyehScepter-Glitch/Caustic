#include "Material.h"

namespace Caustic
{
	Material::Material(const MaterialType& type, const glm::vec3& albedo, bool smoothShading)
		:m_MaterialType(type), m_Albedo(albedo), m_SmoothShading(smoothShading)
	{
	}
}