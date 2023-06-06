#include "Material.h"

namespace Caustic
{
	Material::Material(const std::string& type, const glm::vec3& albedo, bool smoothShading, float ior = 1.0f)
		:m_Albedo(albedo), m_SmoothShading(smoothShading), m_IOR(ior)
	{
		m_MaterialType = StringToType(type);
	}
}