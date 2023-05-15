#include "Triangle.h"
#include "Ray.h"

#include <glm/glm.hpp>
#include <limits>

namespace Caustic
{
    //Basically 0
    constexpr float kEpsilon = 1e-8;

    Triangle::Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2)
        : m_V0(v0)
        , m_V1(v1)
        , m_V2(v2)
    {
        // Calculate surface normal
        m_Normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
        m_Color = glm::normalize(glm::vec3(abs(v0.x + v1.y), abs(v1.y + v2.z), abs(v2.z + v0.x)));
        m_Area = m_Normal.length() / 2;
    }

    bool Triangle::Intersect(const Ray& ray, float& t, float& u, float& v) const
    {
        // Calculate intersection using Moller-Trumbore algorithm
        glm::vec3 edge1 = m_V1 - m_V0;
        glm::vec3 edge2 = m_V2 - m_V0;
        glm::vec3 h = glm::cross(ray.GetDirection(), edge2);
        
        float determinant = glm::dot(edge1, h);
        if (determinant > -kEpsilon && determinant < kEpsilon)
        {
            // Ray is parallel to the triangle plane
            return false;
        }

        float invDet = 1.0f / determinant;
        glm::vec3 distance = ray.GetOrigin() - m_V0;
        u = invDet * glm::dot(distance, h);
        if (u < 0 || u > 1)
        {
            // Intersection is outside the triangle
            return false;
        }

        glm::vec3 q = glm::cross(distance, edge1);
        v = invDet * glm::dot(ray.GetDirection(), q);
        if (v < 0 || u + v > 1)
        {
            // Intersection is outside the triangle
            return false;
        }

        t = invDet * glm::dot(edge2, q);

        if (!t > 0)
        {
            return false;
        }

        if (t > kEpsilon)
        {
            // Intersection is valid
            return true;
        }

        return false;
    }

    bool Triangle::AlternativeIntersect(const Ray& ray, float& t, float& u, float& v) const
    {
        glm::vec3 rayOrigin = ray.GetOrigin();
        glm::vec3 rayDirection = ray.GetDirection();
        glm::vec3 edge1 = m_V1 - m_V0;
        glm::vec3 edge2 = m_V2 - m_V0;

        // D.(E1xE2) = E1.(DxE2)
        // P vector: Cross product of ray direction D and Edge 2
        glm::vec3 pvec = glm::cross(rayDirection, edge2);

        // Determinant:
        // Dot product of D(ray direction) and the Cross product of Edge 1 and Edge2(triangle normal) or
        // Dot product of P vector and Edge 1
        float det = glm::dot(pvec, edge1);

        // If the determinant is negative, the triangle is 'back facing.'
        // If the determinant is close to 0, the ray misses the triangle
        if (det <= 0)
        {
            return false;
        }

        // Inverse Determinant
        float invDet = 1 / det;

        // Compute u
        glm::vec3 tvec = rayOrigin - m_V0;
        u = glm::dot(tvec, pvec) * invDet;
        if (u < 0 || u > 1) return false;

        // Compute v
        glm::vec3 qvec = glm::cross(tvec, edge1);
        v = glm::dot(rayDirection, qvec) * invDet;
        if (v < 0 || u + v > 1) return false;

        // Compute t
        t = glm::dot(edge2, qvec) * invDet;

        return true;
    }
}