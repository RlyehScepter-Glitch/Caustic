#pragma once

#include "Scene/Scene.h"

namespace Caustic
{

	static class Renderer
	{
	public:
		static void GenerateImage(const Scene& scene, const std::string& fileName);
		static Ray GenerateRay(const uint32_t& x, const uint32_t& y, const Scene& scene);
	};

}