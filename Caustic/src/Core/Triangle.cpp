#include "Triangle.h"
#include "Vec3.h"
#include "Ray.h"

#include <limits>

namespace Caustic
{
    const float EPSILON = 1e-6f;

    Triangle::Triangle(const Vec3& v0, const Vec3& v1, const Vec3& v2)
        : m_V0(v0)
        , m_V1(v1)
        , m_V2(v2)
    {
        // Calculate surface normal
        m_Normal = Vec3::Cross(v1 - v0, v2 - v0);
        m_Normal.Normalize();
    }

    bool Triangle::Intersect(const Ray& ray, float& t) const
    {
        // Calculate intersection using Moller-Trumbore algorithm
        Vec3 edge1 = m_V1 - m_V0;
        Vec3 edge2 = m_V2 - m_V0;
        Vec3 h = Vec3::Cross(ray.GetDirection(), edge2);
        float determinant = Vec3::Dot(edge1, h);
        if (determinant > -EPSILON && determinant < EPSILON)
        {
            // Ray is parallel to the triangle plane
            return false;
        }

        float invDet = 1.0f / determinant;
        Vec3 distance = ray.GetOrigin() - m_V0;
        float u = invDet * Vec3::Dot(distance, h);
        if (u < 0 || u > 1)
        {
            // Intersection is outside the triangle
            return false;
        }

        Vec3 q = Vec3::Cross(distance, edge1);
        float v = invDet * Vec3::Dot(ray.GetDirection(), q);
        if (v < 0 || u + v > 1)
        {
            // Intersection is outside the triangle
            return false;
        }

        t = invDet * Vec3::Dot(edge2, q);
        if (t > EPSILON)
        {
            // Intersection is valid
            return true;
        }

        return false;
    }
}