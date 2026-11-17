#include "window.h"
#include "src/util/controller_util.h"

static void framebuffer_size_callback(GLFWwindow* window, GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
}

static GLint initGLFW()
{
    if (glfwInit() != GL_TRUE)
    {
        return GL_FALSE;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    return GL_TRUE;
}

GLFWwindow *initGLFWWindow(GLsizei width, GLsizei height, const std::string title)
{
    if (initGLFW() != GL_TRUE)
    {
        return nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return window;
}
