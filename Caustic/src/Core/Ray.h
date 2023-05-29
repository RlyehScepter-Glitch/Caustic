#pragma once

#include <glm/glm.hpp>

#include <cmath>

namespace Caustic
{
	enum class RayType
	{
		invalid,
		camera,
		shadow,
		reflection,
		refractive
	};

	class Ray
	{
	public:
		//Constructors
		Ray() = default;
		Ray(const glm::vec3& origin, const glm::vec3& direction, RayType type, int depth = 0, float tMin = 0.0f, float tMax = INFINITY)
			: m_Origin(origin), m_Direction(direction), m_RayType(type), m_Depth(depth), m_TMin(tMin), m_TMax(tMax) {}

		glm::vec3 PointAt(float distance) const;

		//Getters
		const glm::vec3 GetOrigin() const { return m_Origin; }
		const glm::vec3 GetDirection() const { return m_Direction; }
		const float GetTMin() const { return m_TMin; }
		const float GetTMax() const { return m_TMax; }
		const int GetDepth() const { return m_Depth; }
		const RayType GetType() const { return m_RayType; }
		
		//Setters
		void SetOrigin(const glm::vec3& origin);
		void SetDirection(const glm::vec3& direction);

	private:
		glm::vec3 m_Origin = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Direction = { 0.0f, 0.0f, -1.0f };
		float m_TMin;
		float m_TMax;
		int m_Depth;
		RayType m_RayType;
	};

}