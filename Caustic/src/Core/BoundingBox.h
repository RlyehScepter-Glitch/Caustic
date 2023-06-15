#pragma once

#include "Ray.h"
#include <glm/glm.hpp>

namespace Caustic
{
	class BoundingBox
	{
	public:
		BoundingBox();
		BoundingBox(const glm::vec3& boxMin, const glm::vec3& boxMax)
			:m_BoxMin(boxMin), m_BoxMax(boxMax) {}

		const glm::vec3& GetMin() const { return m_BoxMin; }
		const glm::vec3& GetMax() const { return m_BoxMax; }

		bool IntersectsBox(const Ray& ray);

	private:
		glm::vec3 m_BoxMin;
		glm::vec3 m_BoxMax;
	};
}