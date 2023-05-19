#pragma once
#include <glm/glm.hpp>

namespace Caustic
{
	class Light
	{
	public:
		// Constructors
		Light() = default;
		Light(uint32_t intensity, const glm::vec3& position);
		
		// Getters
		const int GetIntensity() const { return m_Intensity; }
		const glm::vec3 GetPosition() const { return m_Position; }
		
		// Setters
		// Sets new value to intensity
		void SetIntensity(uint32_t intensity);
		// Sets new position
		void SetPosition(const glm::vec3& position);
		
		// Functionality
		// Moves the light in the input direction (vec3)
		void MoveLight(const glm::vec3& direction);
	private:
		uint32_t m_Intensity;
		glm::vec3 m_Position;
	};
}