#include "Mesh.h"

namespace Caustic
{
	// TODO:: Implement Intersection function
	bool Mesh::Intersect(const Ray& ray) const
	{
		return false;
	}

	void Mesh::PushTriangle(const Triangle& triangle)
	{
		m_Triangles.push_back(triangle);
	}
}