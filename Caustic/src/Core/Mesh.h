#pragma once

#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include "Triangle.h"

namespace Caustic
{
    class Mesh 
    {
    public:
        // Constructors
        Mesh(const std::string& path);

        bool Intersect(const Ray& ray) const;
    private:
        std::vector<Triangle> m_Triangles;
    };
}