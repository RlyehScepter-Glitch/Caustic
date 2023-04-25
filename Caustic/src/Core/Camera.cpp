#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Caustic
{

    Camera::Camera(const glm::vec3& position, const glm::mat4& view)
        : m_Position(position), m_View(view)
    {
        
    }

    Camera::Camera(const glm::vec3& position, const glm::mat4& view, uint32_t width, uint32_t height)
        : m_Position(position), m_View(view), m_Width(width), m_Height(height)
    {

    }

    Camera::Camera(float fov, float nearClip, float farClip)
        : m_FOV(fov), m_NearClip(nearClip), m_FarClip(farClip)
    {

    }

    Camera::Camera(float fov, float nearClip, float farClip, uint32_t width, uint32_t height)
        : m_FOV(fov), m_NearClip(nearClip), m_FarClip(farClip), m_Width(width), m_Height(height)
    {

    }

    Camera::Camera(const glm::vec3& position, const glm::vec3& direction, float fov, float nearClip, float farClip)
        : m_Position(position), m_Direction(direction), m_FOV(fov), m_NearClip(nearClip), m_FarClip(farClip)
    {

    }

    Camera::Camera(const glm::vec3& position, const glm::vec3& direction, float fov, float nearClip, float farClip, uint32_t width, uint32_t height)
        : m_Position(position), m_Direction(direction), m_FOV(fov), m_NearClip(nearClip), m_FarClip(farClip), m_Width(width), m_Height(height)
    {

    }

    void Camera::Dolly(float distance)
    {
        m_Position.z += distance;
    }

    void Camera::Truck(float distance)
    {
        m_Position.x += distance;
    }

    void Camera::Pedestal(float distance)
    {
        m_Position.y += distance;
    }

    void Camera::Pan(float angle)
    {
        m_View = glm::rotate(m_View, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
    }

    void Camera::Tilt(float angle)
    {
        m_View = glm::rotate(m_View, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void Camera::Roll(float angle)
    {
        m_View = glm::rotate(m_View, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    }
}