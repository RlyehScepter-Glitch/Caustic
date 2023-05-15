#pragma once

#include "Ray.h"

#include <glm/glm.hpp>

namespace Caustic
{

    class Camera {
    public:
        // Constructors
        // Default
        Camera() = default;
        // Takes in Postion and View
        Camera(const glm::vec3& position, const glm::mat4& view);
        // Takes in Postion, View, Width and Height
        Camera(const glm::vec3& position, const glm::mat4& view, uint32_t width, uint32_t height);
        // Takes in Vertical FOV(in Degrees), Near Clip, Far Clip
        Camera(float fov, float nearClip, float farClip);
        // Takes in Vertical FOV(in Degrees), Near Clip, Far Clip, Width and Height
        Camera(float fov, float nearClip, float farClip, uint32_t width, uint32_t height);
        // Takes in Camera Position, Camera Direction, Vertical FOV(in Degrees), Near Clip, Far Clip
        Camera(const glm::vec3& position, const glm::vec3& direction, float fov, float nearClip, float farClip);
        // Takes in Camera Position, Camera Direction, Vertical FOV(in Degrees), Near Clip, Far Clip, Width and Height
        Camera(const glm::vec3& position, const glm::vec3& direction, float fov, float nearClip, float farClip, uint32_t width, uint32_t height);

        // Getters
        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

        const float& GetNearClip() const { return m_NearClip; }
        const float& GetFarClip() const { return m_FarClip; }
        
        const glm::vec3& GetPosition() const { return m_Position; }
        const glm::vec3& GetDirection() const { return m_Direction; }

        // Setters
        void SetViewMatrix(const glm::mat4& matrix);
        void SetPosition(const glm::vec3& position);

        // Movement functions
        void Dolly(float distance);
        void Truck(float distance);
        void Pedestal(float distance);
        void Pan(float angle);
        void Tilt(float angle);
        void Roll(float angle);

    private:
        glm::mat4 m_ProjectionMatrix{ 1.0f };
        glm::mat4 m_ViewMatrix{ 1.0f };
        
        float m_FOV = 45.0f;
        float m_NearClip = 0.0f;
        float m_FarClip = 100.0f;

        glm::vec3 m_Position { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_Direction { 0.0f, 0.0f, -1.0f };

        uint32_t m_Width = 1920, m_Height = 1080;
    };

}