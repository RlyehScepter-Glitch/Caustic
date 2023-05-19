#pragma once

#include "Scene/Scene.h"

namespace Caustic
{

	static class Renderer
	{
	public:
		static void GenerateImage(const Scene& scene);
	};

}