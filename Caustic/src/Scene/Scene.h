#pragma once

#include "Core/Camera.h"
#include "Core/Mesh.h"
#include "Settings.h"

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

		//Getters
		const Camera& GetCamera() const { return m_Camera; }
		const Settings& GetSettings() const { return m_Settings; }
		const std::vector<Mesh>& GetObjects() const { return m_Objects; }

	private:
		void ParseSceneFile(const std::string& sceneFileName);
	private:
		std::vector<Mesh> m_Objects;
		Camera m_Camera;
		Settings m_Settings;
	};
}