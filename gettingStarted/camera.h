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
        cameraUp = glm::vec3(0.0f, 2.0f, 0.0f);
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        jumpPos = glm::vec3(0.0f, jumpOffset, 0.0f);
        jumpingUp = true;
        jumping = false;
        jumpHeight = 0.0f;
    }
    /**
     * @brief start jumping phase
     *
     */
    void startJump()
    {
        if (!jumping)
        {
            jumping = true;
        }
    }
    /**
     * @brief Calculate the offset for jumping
     *
     */
    void jumpCalc()
    {
        if (jumping)
        {
            if (jumpingUp)
            {
                std::cout << "upping jump" << std::endl;
                jumpHeight += jumpOffset;
                if (jumpHeight >= 2.0f)
                {
                    std::cout << "jumpup to false" << std::endl;
                    jumpingUp = false;
                }
            }
            else
            {
                std::cout << "lowering jump" << std::endl;
                jumpHeight -= jumpOffset;
                if (jumpHeight <= 0)
                {
                    std::cout << "jumping to false" << std::endl;
                    jumping = false;
                    jumpingUp = true;
                }
            }
        }
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
        if(jumping){
            jumpCalc();
            jumpPos = cameraPos;
            jumpPos.y += jumpHeight;
            return glm::lookAt(jumpPos, jumpPos + cameraFront, cameraUp);
        }
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
    // void goUp()
    // {
    //     cameraPos += glm::normalize(glm::cross(cameraFront, )) * cameraSpeed;
    // }
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
    glm::vec3 jumpPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 direction;
    bool jumping;
    bool jumpingUp;
    float jumpHeight;
    float jumpOffset = 0.1f;
};
#endif