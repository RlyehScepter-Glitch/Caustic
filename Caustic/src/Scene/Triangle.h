#pragma once

#include "Core/Ray.h"

#include <glm/glm.hpp>

namespace Caustic
{
    class Triangle 
    {
    public:
        Triangle(const glm::vec3 & v0, const glm::vec3& v1, const glm::vec3& v2);

        bool Intersect(const Ray& ray, float& t, float& u, float& v) const;
        bool ShadowIntersect(const Ray& ray, float& t, float& u, float& v) const;

        const glm::vec3 GetNormal() const { return m_Normal; }
        const glm::vec3 GetColor() const { return m_Color; }
    private:
        glm::vec3 m_V0;  // First vertex
        glm::vec3 m_V1;  // Second vertex
        glm::vec3 m_V2;  // Third vertex
        glm::vec3 m_Normal;  // Surface normal
        glm::vec3 m_Color; // Albedo
        float m_Area;
    };

}