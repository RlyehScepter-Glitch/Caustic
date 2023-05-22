#pragma once
#include <string>
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
		Material(const std::string& type, const glm::vec3& albedo, bool smoothShading);

		//Getters
		const MaterialType& GetMaterialType() const { return m_MaterialType; }
		const glm::vec3& GetAlbedo() const { return m_Albedo; }
		const bool SmoothShading() const { return m_SmoothShading; }

	private:
		MaterialType m_MaterialType = MaterialType::diffuse;
		glm::vec3 m_Albedo = { 1.0f, 1.0f, 1.0f };
		bool m_SmoothShading = false;
	
	private:
		MaterialType StringToType(const std::string& type)
		{
			if (type == "diffuse")
				return MaterialType::diffuse;

			//Returns Default type
			return MaterialType::diffuse;
		}
	};

}
