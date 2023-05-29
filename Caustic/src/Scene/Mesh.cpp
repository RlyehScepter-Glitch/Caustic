#include "Mesh.h"

namespace Caustic
{
	void Mesh::PushVertex(const Vertex& vertex)
	{
		m_Vertices.push_back(vertex);
	}

	void Mesh::PushTriangle(const Triangle& triangle)
	{
		m_Triangles.push_back(triangle);
	}
	
	void Mesh::PushTriangleIndexToVertex(const uint32_t& vertexIdx, const uint32_t& triangleIdx)
	{
		m_Vertices[vertexIdx].PushTriangleIndex(triangleIdx);
	}
	
	void Mesh::UpdateVertexNormals()
	{
		for (uint32_t i = 0; i < m_Vertices.size(); i++)
		{
			glm::vec3 vertexNormal(0.0f, 0.0f, 0.0f);
			const Vertex& currentVert = m_Vertices[i];

			for (const uint32_t& idx : currentVert.GetTriangleIndices())
			{
				vertexNormal += m_Triangles[idx].GetTriangleNormal();
			}

			m_Vertices[i].UpdateNormal(glm::normalize(vertexNormal));
		}
	}
}