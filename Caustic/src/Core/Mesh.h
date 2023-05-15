#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Triangle.h"

namespace Caustic
{
    class Mesh 
    {
    public:
        // Constructors
        Mesh() = default;

        bool Intersect(const Ray& ray, float nearClip, float &tNear, uint32_t& triIndex, glm::vec2& uv) const;

        const std::vector<Triangle>& GetTriangles() const { return m_Triangles; }

        void PushTriangle(const Triangle& triangle);
    private:
        std::vector<Triangle> m_Triangles;
    };
}