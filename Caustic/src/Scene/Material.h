#pragma once
#include <glm/glm.hpp>

namespace Caustic
{
	enum class MaterialType
	{
	diffuse
	};

	class Material
	{
	public:
		//Constructors
		Material() = default;
		Material(const MaterialType& type, const glm::vec3& albedo, bool smoothShading);

		//Getters
		const MaterialType& GetMaterialType() const { return m_MaterialType; }
		const glm::vec3& GetAlbedo() const { return m_Albedo; }
		bool SmoothShading() { return m_SmoothShading; }

	private:
		MaterialType m_MaterialType = MaterialType::diffuse;
		glm::vec3 m_Albedo = { 1.0f, 1.0f, 1.0f };
		bool m_SmoothShading = false;
	};

}
