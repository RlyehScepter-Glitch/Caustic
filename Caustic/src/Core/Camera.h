#pragma once

#include "Ray.h"

#include <glm/glm.hpp>

namespace Caustic
{

    class Camera {
    public:
        // Constructor
        // Takes in position(origin), target(direction), up vector(Y), FOV, Aspect Ration
        Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float aspectRatio);

        // Getters
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;
        
        // Setters
        void SetAspectRatio(float aspectRatio);
        void SetFOV(float fov);

        // Movement functions
        void Dolly(float distance);
        void Truck(float distance);
        void Pedestal(float distance);
        void Pan(float angle);
        void Tilt(float angle);
        void Roll(float angle);


    private:
        glm::vec3 m_Position;
        glm::vec3 m_Direction;
        glm::vec3 m_Up;
        float m_Fov;
        float m_AspectRatio;

        glm::vec3 m_Right;
        glm::vec3 m_Front;
        glm::vec3 m_WorldUp;

        void UpdateVectors();
    };

}