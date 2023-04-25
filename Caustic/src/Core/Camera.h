#pragma once

#include "Ray.h"

#include <glm/glm.hpp>

namespace Caustic
{

    class Camera {
    public:
        // Constructors
        // Takes in Postion and View
        Camera(const glm::vec3& position, const glm::mat4& view);
        // Takes in Vertical FOV(in Degrees), Near Clip, Far Clip
        Camera(float fov, float nearClip, float farClip);
        // Takes in Camera Position, Camera Direction, Vertical FOV(in Degrees), Near Clip, Far Clip
        Camera(const glm::vec3& position, const glm::vec3& direction, float fov, float nearClip, float farClip);

        // Getters
        const glm::mat4& GetProjectionMatrix() const { return m_Projection; }
        const glm::mat4& GetViewMatrix() const { return m_View; }
        
        const glm::vec3& GetPosition() const { return m_Position; }
        const glm::vec3& GetDirection() const { return m_Direction; }

        // Movement functions
        void Dolly(float distance);
        void Truck(float distance);
        void Pedestal(float distance);
        void Pan(float angle);
        void Tilt(float angle);
        void Roll(float angle);

    private:
        glm::mat4 m_Projection{ 1.0f };
        glm::mat4 m_View{ 1.0f };
        
        float m_FOV = 45.0f;
        float m_NearClip = 0.1f;
        float m_FarClip = 10.0f;

        glm::vec3 m_Position { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_Direction { 0.0f, 0.0f, -1.0f };

        uint32_t m_Width = 0, m_Height = 0;
    };

}