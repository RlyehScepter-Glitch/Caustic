#pragma once

#include "Camera.h"
#include "Mesh.h"

#include <vector>
#include <glm/glm.hpp>
#include <iostream>

namespace Caustic
{

	class Scene
	{
	public:
		// Constructor
		Scene(const std::string& sceneFileName);

	private:
		std::vector<Mesh> m_Objects;
		Camera m_Camera;
		SceneSettings m_Settings;
	};

}