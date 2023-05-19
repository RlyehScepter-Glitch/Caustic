#include "Triangle.h"

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
        m_Area = m_Normal.length() / 2.0f;
    }

    bool Triangle::Intersect(const Ray& ray, float& t, float& u, float& v) const
    {
        glm::vec3 rayOrigin = ray.GetOrigin();
        glm::vec3 rayDirection = ray.GetDirection();
        glm::vec3 edge1 = m_V1 - m_V0;
        glm::vec3 edge2 = m_V2 - m_V0;

        // E1xE2 = Normal
        // D.(E1xE2) = E1.(DxE2)
        // P vector: Cross product of ray direction D and Edge 2
        glm::vec3 pvec = glm::cross(rayDirection, edge2);

        // Determinant:
        // Dot product of D(ray direction) and the Cross product of Edge 1 and Edge2(triangle normal) or
        // Dot product of P vector and Edge 1
        float det = glm::dot(pvec, edge1);

        // If the determinant is negative, the triangle is 'back facing.'
        // If the determinant is close to 0, the ray misses the triangle
        if (det <= kEpsilon)
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

    bool Triangle::ShadowIntersect(const Ray& ray, float& t, float& u, float& v) const
    {
        glm::vec3 rayOrigin = ray.GetOrigin();
        glm::vec3 rayDirection = ray.GetDirection();
        glm::vec3 edge1 = m_V1 - m_V0;
        glm::vec3 edge2 = m_V2 - m_V0;

        // E1xE2 = Normal
        // D.(E1xE2) = E1.(DxE2)
        // P vector: Cross product of ray direction D and Edge 2
        glm::vec3 pvec = glm::cross(rayDirection, edge2);

        // Determinant:
        // Dot product of D(ray direction) and the Cross product of Edge 1 and Edge2(triangle normal) or
        // Dot product of P vector and Edge 1
        float det = glm::dot(pvec, edge1);

        // If the determinant is negative, the triangle is 'back facing.'
        // If the determinant is close to 0, the ray misses the triangle
        if (det == 0)
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
        if (t <= 0)
            return false;

        return true;
    }
}