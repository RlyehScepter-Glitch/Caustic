#pragma once

#include <glm/glm.hpp>

namespace Caustic
{
	class Settings
	{
	public:
		//Constructors
		//Default
		Settings() = default;
		//Takes Background Color, Width and Height
		Settings(const glm::vec3& backgroundColor, uint32_t width, uint32_t height);

		//Setters
		void SetBackgroundColor(const glm::vec3& bgColor);
		void SetWidth(uint32_t width);
		void SetHeight(uint32_t height);

	private:
		glm::vec3 m_BackgroundColor = { 0.0f, 0.0f, 0.0f };
		uint32_t m_Width = 1920, m_Height = 1080;
	};
}