#include "Mesh.h"

namespace Caustic
{
    Mesh::Mesh(uint32_t materialIdx)
        :m_MaterialIdx(materialIdx)
    {
    }

    //Takes in a Ray, Camera nearclip(nearClip), Nearest distance(tNear), Triangle index(triIndex), Barycentric coordinates of the intersection point(uv)
	bool Mesh::Intersect(const Ray& ray, float nearClip, float& tNear, uint32_t& triIndex, glm::vec2& uv) const
	{
        bool intersected = false;
        
        for (size_t i = 0; i < m_Triangles.size(); i++)
        {
            //t, u and v set inside Triangle Intersect function
            float t;
            float u;
            float v;

            if (m_Triangles[i].Intersect(ray, t, u, v) && t <= tNear && t > 0)
            {
                tNear = t;
                triIndex = i;
                uv.x = u;
                uv.y = v;
                intersected = true;
            }

        }

        return intersected;
	}

    bool Mesh::ShadowIntersect(const Ray& ray) const
    {
        bool intersected = false;

        for (size_t i = 0; i < m_Triangles.size(); i++)
        {
            //t, u and v set inside Triangle Intersect function
            float t;
            float u;
            float v;

            if (m_Triangles[i].ShadowIntersect(ray, t, u, v))
            {
                intersected = true;
            }

        }

        return intersected;
    }

	void Mesh::PushTriangle(const Triangle& triangle)
	{
		m_Triangles.push_back(triangle);
	}
}