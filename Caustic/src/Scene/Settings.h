#pragma once

#include <glm/glm.hpp>

namespace Caustic
{
	class Settings
	{
	public:
		Settings(const glm::vec3& backgroundColor, uint32_t width, uint32_t height);
	private:
		glm::vec3 m_BackgroundColor;
		uint32_t m_Width, m_Height;
	};
}