#include "Triangle.h"

#include <glm/glm.hpp>
#include <limits>

namespace Caustic
{
    //Basically 0
    constexpr double kEpsilon = 1e-8;

    //m_MeshIdx is set on creation of Triangle in Scene
    Triangle::Triangle(uint32_t v0, uint32_t v1, uint32_t v2, const std::vector<Vertex>& vertices, const uint32_t& meshIdx)
        : m_V0(v0)
        , m_V1(v1)
        , m_V2(v2)
        , m_MeshIdx(meshIdx)
    {
        m_TriangleNormal = glm::normalize(glm::cross(vertices[v1].GetCoordinates() - vertices[v0].GetCoordinates(), vertices[v2].GetCoordinates() - vertices[v0].GetCoordinates()));
        m_Area = m_TriangleNormal.length() / 2.0f;
        m_Color = glm::normalize(glm::vec3(glm::abs(vertices[v0].GetCoordinates().x + vertices[v1].GetCoordinates().y),
                  glm::abs(vertices[v1].GetCoordinates().y + vertices[v2].GetCoordinates().z),
                  glm::abs(vertices[v2].GetCoordinates().z + vertices[v0].GetCoordinates().x)));
    }

    bool Triangle::Intersect(const Ray& ray, float& t, float& u, float& v, const std::vector<Vertex>& vertices) const
    {
        glm::vec3 rayOrigin = ray.GetOrigin();
        glm::vec3 rayDirection = ray.GetDirection();
        glm::vec3 edge1 = vertices[m_V1].GetCoordinates() - vertices[m_V0].GetCoordinates();
        glm::vec3 edge2 = vertices[m_V2].GetCoordinates() - vertices[m_V0].GetCoordinates();

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
        //CameraRay
        if (det <= kEpsilon && (ray.GetType() == RayType::camera || ray.GetType() == RayType::reflection))
        {
            return false;
        }
        //ShadowRay
        if (det == 0 && ray.GetType() == RayType::shadow)
        {
            return false;
        }

        // Inverse Determinant
        float invDet = 1 / det;

        // Compute u
        glm::vec3 tvec = rayOrigin - vertices[m_V0].GetCoordinates();
        u = glm::dot(tvec, pvec) * invDet;
        if (u < 0 || u > 1) return false;

        // Compute v
        glm::vec3 qvec = glm::cross(tvec, edge1);
        v = glm::dot(rayDirection, qvec) * invDet;
        if (v < 0 || u + v > 1) return false;

        // Compute t
        t = glm::dot(edge2, qvec) * invDet;

        if (t <= 0 && ray.GetType() == RayType::shadow)
            return false;

        return true;
    }
}