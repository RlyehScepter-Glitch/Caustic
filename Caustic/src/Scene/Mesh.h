#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Core/Triangle.h"

namespace Caustic
{
    class Mesh 
    {
    public:
        // Constructors
        Mesh() = default;
        Mesh(uint32_t materialIdx);

        bool Intersect(const Ray& ray, float nearClip, float &tNear, uint32_t& triIndex, glm::vec2& uv) const;
        bool ShadowIntersect(const Ray& ray) const;

        const uint32_t GetMaterialIdx() const { return m_MaterialIdx; }
        const std::vector<Triangle>& GetTriangles() const { return m_Triangles; }

        void PushTriangle(const Triangle& triangle);
    private:
        uint32_t m_MaterialIdx = 0;
        std::vector<Triangle> m_Triangles;
    };
}