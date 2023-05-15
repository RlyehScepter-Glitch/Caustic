#include "Mesh.h"

namespace Caustic
{
    //Takes in a Ray, Camera nearclip(nearClip), Nearest distance(tNear), Triangle index(triIndex), Barycentric coordinates of the intersection point(uv)
	bool Mesh::Intersect(const Ray& ray, float nearClip, float& tNear, uint32_t& triIndex, glm::vec2& uv) const
	{
        for (size_t i = 0; i < m_Triangles.size(); i++)
        {
            float t = FLT_MAX;

            // u and v set inside Triangle Intersect function
            float u;
            float v;

            if (m_Triangles[i].AlternativeIntersect(ray, t, u, v) && t > tNear)
            {
                tNear = t;
                triIndex = i;
                uv.x = u;
                uv.y = v;
                return true;
            }

        }

        return false;
	}

	void Mesh::PushTriangle(const Triangle& triangle)
	{
		m_Triangles.push_back(triangle);
	}
}