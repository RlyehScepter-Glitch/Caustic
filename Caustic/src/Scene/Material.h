#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Caustic
{
	enum class MaterialType
	{
	diffuse,
	reflective,
	refractive,
	constant
	};

	class Material
	{
	public:
		//Constructors
		Material() = default;
		Material(const std::string& type, const glm::vec3& albedo, bool smoothShading, bool culling, float ior = 1.0f);

		//Getters
		const MaterialType& GetMaterialType() const { return m_MaterialType; }
		const glm::vec3& GetAlbedo() const { return m_Albedo; }
		const float& GetIOR() const { return m_IOR; }
		const bool SmoothShading() const { return m_SmoothShading; }
		const bool Culling() const { return m_BackfaceCulling; }

	private:
		MaterialType m_MaterialType = MaterialType::diffuse;
		glm::vec3 m_Albedo = { 1.0f, 1.0f, 1.0f };
		float m_IOR;
		bool m_SmoothShading = false;
		bool m_BackfaceCulling = true;
	
	private:
		MaterialType StringToType(const std::string& type)
		{
			if (type == "diffuse")
				return MaterialType::diffuse;
			if (type == "reflective")
				return MaterialType::reflective;
			if (type == "refractive")
				return MaterialType::refractive;
			if (type == "constant")
				return MaterialType::constant;

			//Returns Default type
			return MaterialType::diffuse;
		}
	};

}
