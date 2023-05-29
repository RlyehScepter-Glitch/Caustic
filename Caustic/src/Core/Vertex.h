#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace Caustic
{
	class Vertex
	{
	public:
		Vertex(float x, float y, float z)
		{
			m_Coordinates = { x, y, z };
		}

		const glm::vec3& GetCoordinates() const { return m_Coordinates; }
		const glm::vec3& GetVertexNormal() const { return m_VertexNormal; }
		const std::vector<uint32_t>& GetTriangleIndices() const { return m_TriangleIndices; }

		void UpdateNormal(const glm::vec3& normal);
		void PushTriangleIndex(const uint32_t& triIdx);
	private:
		glm::vec3 m_Coordinates;
		glm::vec3 m_VertexNormal;
		std::vector<uint32_t> m_TriangleIndices;
	};
}