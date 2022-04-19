#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>
class Camera
{
public:
    Camera()
    {
        yaw = -90.0f;
        pitch = 0.0f;
        cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
        cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    }
    glm::vec3 getcameraPos()
    {
        return cameraPos;
    }
    glm::vec3 getCameraFront()
    {
        return cameraFront;
    }
    glm ::vec3 getCameraUp()
    {
        return cameraUp;
    }
    glm::mat4 lookAt()
    {
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);
        return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }
    void goRight()
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    void goLeft()
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    void goForward()
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    void goBackward()
    {
        cameraPos -= cameraSpeed * cameraFront;
    }
    void pitchUp()
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        else
        {
            pitch += offset;
        }
    }
    void pitchDown()
    {
        if (pitch < -89.0f)
            pitch = -89.0f;
        else
        {
            pitch -= offset;
        }
    }
    void yawUp()
    {
        yaw += offset;
    }
    void yawDown()
    {
        yaw -= offset;
    }

private:
    const float offset = 1.0f;
    const float cameraSpeed = 0.05f;
    float yaw;
    float pitch;
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 direction;
};
#endif