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

		//Getters
		const glm::vec3& GetBackgroundColor() const { return m_BackgroundColor; }
		const uint32_t& GetWidth() const { return m_Width; }
		const uint32_t& GetHeight() const  { return m_Height; }
		const float& GetAspectRatio() const  { return m_AspectRatio; }

		//Setters
		void SetBackgroundColor(const glm::vec3& bgColor);
		void SetWidth(uint32_t width);
		void SetHeight(uint32_t height);
		void SetGI(bool gi);
		void SetReflections(bool refl);
		void SetRefractions(bool refract);

		void UpdateAspectRatio();

	private:
		glm::vec3 m_BackgroundColor = { 0.0f, 0.0f, 0.0f };
		uint32_t m_Width = 1920, m_Height = 1080;
		float m_AspectRatio = 16.0f / 9.0f;
		bool m_GlobalIllumination = false;
		bool m_Reflections = false;
		bool m_Refractions = false;
	};
}