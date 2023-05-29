#include "Vertex.h"

namespace Caustic
{
	void Vertex::UpdateNormal(const glm::vec3& normal)
	{
		m_VertexNormal = normal;
	}

	void Vertex::PushTriangleIndex(const uint32_t& triIdx)
	{
		m_TriangleIndices.push_back(triIdx);
	}
}