#include "Triangle.h"
#include "Ray.h"

#include <glm/glm.hpp>
#include <limits>

namespace Caustic
{
    const float EPSILON = 1e-6f;

    Triangle::Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2)
        : m_V0(v0)
        , m_V1(v1)
        , m_V2(v2)
    {
        // Calculate surface normal
        m_Normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
        m_Color = glm::normalize(glm::vec3(abs(v0.x + v1.y), abs(v1.y + v2.z), abs(v2.z + v0.x)));
    }

    bool Triangle::Intersect(const Ray& ray, float t) const
    {
        // Calculate intersection using Moller-Trumbore algorithm
        glm::vec3 edge1 = m_V1 - m_V0;
        glm::vec3 edge2 = m_V2 - m_V0;
        glm::vec3 h = glm::cross(ray.GetDirection(), edge2);
        float determinant = glm::dot(edge1, h);
        if (determinant > -EPSILON && determinant < EPSILON)
        {
            // Ray is parallel to the triangle plane
            return false;
        }

        float invDet = 1.0f / determinant;
        glm::vec3 distance = ray.GetOrigin() - m_V0;
        float u = invDet * glm::dot(distance, h);
        if (u < 0 || u > 1)
        {
            // Intersection is outside the triangle
            return false;
        }

        glm::vec3 q = glm::cross(distance, edge1);
        float v = invDet * glm::dot(ray.GetDirection(), q);
        if (v < 0 || u + v > 1)
        {
            // Intersection is outside the triangle
            return false;
        }

        t = invDet * glm::dot(edge2, q);
        if (t > EPSILON)
        {
            // Intersection is valid
            return true;
        }

        return false;
    }
}