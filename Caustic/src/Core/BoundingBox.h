#pragma once

#include "Ray.h"
#include <glm/glm.hpp>

namespace Caustic
{
	class BoundingBox
	{
	public:
		BoundingBox() = default;
		BoundingBox(const glm::vec3& boxMin, const glm::vec3& boxMax)
			:m_BoxMin(boxMin), m_BoxMax(boxMax) {}

		const glm::vec3& GetMin() const { return m_BoxMin; }
		const glm::vec3& GetMax() const { return m_BoxMax; }

		void SetMin(const glm::vec3& boxMin);
		void SetMax(const glm::vec3& boxMax);

		const bool IntersectsBox(const Ray& ray) const;
		static const bool BoxesIntersection(const BoundingBox& boxA, const BoundingBox& boxB);
		const void Split(uint32_t axisIdx, BoundingBox& boxA, BoundingBox& boxB) const;

	private:
		glm::vec3 m_BoxMin;
		glm::vec3 m_BoxMax;
	};
}