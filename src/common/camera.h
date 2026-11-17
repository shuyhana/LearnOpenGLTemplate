#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "macro.h"
#include "singleton.h"

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const GLfloat YAW         = -90.0f;
const GLfloat PITCH       = 0.0f;
const GLfloat SPEED       = 2.5f;
const GLfloat SENSITIVITY = 0.1f;
const GLfloat ZOOM        = 45.0f;

class Camera : public Singleton<Camera>
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           GLfloat yaw = YAW,
           GLfloat pitch = PITCH);
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

    ~Camera() = default;

    glm::mat4 GetViewMatrix() const
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void ProcessKeyboard(CameraMovement direction, float deltaTime);
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = GL_TRUE);
    void ProcessMouseScroll(GLfloat yoffset);

    /// @copydoc Singleton::getSingleton()
    static Camera& getInstance(void);
    /// @copydoc Singleton::getSingleton()
    static Camera* getSingletonPtr(void);
#if 0
    static Camera& getInstance()
    {
        if (!camera)
        {
            camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
        }

        return *camera;
    }
#endif
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    GLfloat Yaw;
    GLfloat Pitch;

    GLfloat MovementSpeed;
    GLfloat MouseSensitivity;
    GLfloat Zoom;

    bool firstMouse = true;
    GLfloat lastX = (GLfloat)SCR_WIDTH / 2.0f;
    GLfloat lastY = (GLfloat)SCR_HEIGHT / 2.0f;

private:
    void updateCameraVectors();

    //static Camera* camera;
};
