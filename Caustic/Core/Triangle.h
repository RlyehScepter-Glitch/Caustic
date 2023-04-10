#pragma once

#include "Vec3.h"

namespace Caustic
{
    class Triangle {
    public:
        Triangle(const Vec3& v0, const Vec3& v1, const Vec3& v2);

        bool Intersect(const Vec3& origin, const Vec3& direction, float& t) const;

    private:
        Vec3 m_V0;  // First vertex
        Vec3 m_V1;  // Second vertex
        Vec3 m_V2;  // Third vertex
        Vec3 m_Normal;  // Surface normal
    };

}