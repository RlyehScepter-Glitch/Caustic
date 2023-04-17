#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Caustic
{

    Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up, float fov, float aspectRatio)
        : m_Position(position), m_Direction(direction), m_Up(up), m_Fov(fov), m_AspectRatio(aspectRatio)
    {
        UpdateVectors();
    }

    void Camera::SetAspectRatio(float aspectRatio)
    {
        m_AspectRatio = aspectRatio;
    }

    void Camera::SetFOV(float fov)
    {
        m_Fov = fov;
    }

    void Camera::Dolly(float distance)
    {
        m_Position += distance * m_Front;
        m_Direction += distance * m_Front;
        UpdateVectors();
    }

    void Camera::Truck(float distance)
    {
        m_Position += distance * m_Right;
        m_Direction += distance * m_Right;
        UpdateVectors();
    }

    void Camera::Pedestal(float distance)
    {
        m_Position += distance * m_WorldUp;
        m_Direction += distance * m_WorldUp;
        UpdateVectors();
    }

    void Camera::Pan(float angle)
    {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_WorldUp);
        m_Front = glm::vec3(rotation * glm::vec4(m_Front, 1.0f));
        m_Right = glm::vec3(rotation * glm::vec4(m_Right, 1.0f));
        UpdateVectors();
    }

    void Camera::Tilt(float angle)
    {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_Right);
        m_Front = glm::vec3(rotation * glm::vec4(m_Front, 1.0f));
        m_Up = glm::vec3(rotation * glm::vec4(m_Up, 1.0f));
        UpdateVectors();
    }

    void Camera::Roll(float angle)
    {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_Front);
        m_Up = glm::vec3(rotation * glm::vec4(m_Up, 1.0f));
        m_Right = glm::vec3(rotation * glm::vec4(m_Right, 1.0f));
        UpdateVectors();
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        return glm::lookAt(m_Position, m_Direction, m_Up);
    }

    glm::mat4 Camera::GetProjectionMatrix() const
    {
        return glm::perspective(glm::radians(m_Fov), m_AspectRatio, 0.1f, 1000.0f);
    }

    void Camera::UpdateVectors()
    {
        m_Front = glm::normalize(m_Direction - m_Position);
        m_Right = glm::normalize(glm::cross(m_Front, m_Up));
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    }

}