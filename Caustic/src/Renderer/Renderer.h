#pragma once

#include "Scene/Scene.h"

namespace Caustic
{
	static class Renderer
	{
	public:
		static void GenerateImage(const Scene& scene, const std::string& fileName);
		static Ray GenerateCameraRay(const uint32_t& x, const uint32_t& y, const Scene& scene);
		static glm::vec3 Shade(const Ray& ray, const IntersectionData& data, const Scene& scene);
		static glm::vec3 ShadeDiffuse(const Ray& ray, const IntersectionData& data, const Scene& scene);
		static glm::vec3 ShadeReflective(const Ray& ray, const IntersectionData& data, const Scene& scene);
		static glm::vec3 ShadeRefractive(const Ray& ray, const IntersectionData& data, const Scene& scene);
		static glm::vec3 ShadeConstant(const Ray& ray, const IntersectionData& data, const Scene& scene);
	};

}