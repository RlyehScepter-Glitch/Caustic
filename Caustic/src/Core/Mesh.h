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

        bool Intersect(const Ray& ray) const;

        void PushTriangle(const Triangle& triangle);
    private:
        std::vector<Triangle> m_Triangles;
    };
}