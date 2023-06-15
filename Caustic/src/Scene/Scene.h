#pragma once

#include "Camera.h"
#include "Mesh.h"
#include "Light.h"
#include "Core/BoundingBox.h"
#include "Settings.h"
#include "Material.h"
#include "Core/Vertex.h"
#include "Core/Triangle.h"

#include <vector>
#include <glm/glm.hpp>
#include <iostream>

namespace Caustic
{
	struct IntersectionData
	{
		glm::vec3 hitPoint;
		glm::vec3 hitPointNormal;
		glm::vec3 interpolatedVertexNormal;
		glm::vec2 UV;
		int materialIdx;
		int objectIdx;
		float materialIOR;
		int triangleIdx = -1;
	};

	class Scene
	{
	public:
		// Constructor
		Scene(const std::string& sceneFileName);

		//Getters
		const Camera& GetCamera() const { return m_Camera; }
		const Settings& GetSettings() const { return m_Settings; }
		const std::vector<Mesh>& GetObjects() const { return m_Objects; }
		const std::vector<Light>& GetLights() const { return m_Lights; }
		const std::vector<Material>& GetMaterials() const { return m_Materials; }

		IntersectionData TraceRay(const Ray& ray, float tNear = FLT_MAX) const;
	private:
		void ParseSceneFile(const std::string& sceneFileName);
	private:
		Camera m_Camera;
		Settings m_Settings;
		std::vector<Mesh> m_Objects;
		std::vector<Light> m_Lights;
		std::vector<Material> m_Materials;
	public:
		BoundingBox m_BoundingBox;
	};
}