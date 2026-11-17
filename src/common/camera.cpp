#include "camera.h"
#include <iostream>

//Camera* Camera::camera = nullptr;
#if 1
template<> Camera* Singleton<Camera>::msSingleton = 0;
Camera* Camera::getSingletonPtr(void)
{
    return msSingleton;
}
Camera& Camera::getInstance(void)
{
    if (!msSingleton)
    {
        msSingleton = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    }
    return ( *msSingleton );
}
#endif
Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) :
    Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) :
    Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    switch (direction)
    {
    case FORWARD:
        Position += Front * velocity;
        break;
    case BACKWARD:
        Position -= Front * velocity;
        break;
    case LEFT:
        Position -= Right * velocity;
        break;
    case RIGHT:
        Position += Right * velocity;
        break;
    default:
        break;
    }
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    std::cout << "xoffset:" << xoffset << ",yoffset:" << yoffset << std::endl;

    Yaw += xoffset;
    Pitch += yoffset;



    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    //std::cout << "Yaw:" << Yaw << ",Pitch:" << Pitch << std::endl;

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    //std::cout << "Yaw:" << Yaw << ",Pitch:" << Pitch << std::endl;

    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up    = glm::normalize(glm::cross(Right, Front));

    std::cout << "Yaw:" << Yaw << ",Pitch:" << Pitch << ",Front:" << Front.x << "," << Front.y << "," << Front.z << std::endl;
    std::cout << "WorldUp:" << WorldUp.x << "," << WorldUp.y << "," << WorldUp.z << std::endl;
    std::cout << "Right:" << Right.x << "," << Right.y << "," << Right.z << std::endl;
    std::cout << "Up:" << Up.x << "," << Up.y << "," << Up.z << std::endl;
}
