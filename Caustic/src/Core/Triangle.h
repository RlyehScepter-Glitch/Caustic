#pragma once

#include "Ray.h"
#include "Vertex.h"

#include <memory>
#include <glm/glm.hpp>

namespace Caustic
{
    class Triangle 
    {
    public:
        Triangle(uint32_t v0, uint32_t v1, uint32_t v2, const std::vector<Vertex>& vertices, const uint32_t& meshIdx);

        bool Intersect(const Ray& ray, float& t, float& u, float& v, const std::vector<Vertex>& vertices) const;

        const uint32_t& GetVertex0() const { return m_V0; }
        const uint32_t& GetVertex1() const { return m_V1; }
        const uint32_t& GetVertex2() const { return m_V2; }
        const uint32_t& GetMeshIndex() const { return m_MeshIdx; }
        const glm::vec3& GetTriangleNormal() const { return m_TriangleNormal; }
        const glm::vec3& GetColor() const { return m_Color; }

    private:
        uint32_t m_V0;  // Index of First vertex
        uint32_t m_V1;  // Index of Second vertex
        uint32_t m_V2;  // Index of Third vertex
        uint32_t m_MeshIdx;  // Index of the Mesh the Triangle belongs to
        glm::vec3 m_TriangleNormal;  // Surface normal
        glm::vec3 m_Color = { 1.0f, 1.0f, 1.0f }; // Color | Might remove later;
        float m_Area;
    };

}