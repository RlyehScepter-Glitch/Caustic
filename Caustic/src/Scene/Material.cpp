#include "Material.h"

namespace Caustic
{
	Material::Material(const std::string& type, const glm::vec3& albedo, bool smoothShading, bool culling, float ior)
		:m_Albedo(albedo), m_SmoothShading(smoothShading), m_BackfaceCulling(culling), m_IOR(ior)
	{
		m_MaterialType = StringToType(type);
	}
}