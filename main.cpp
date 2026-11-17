#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "src/common/macro.h"
#include "src/common/window.h"
#include "src/common/shader.h"
#include "src/common/model.h"
#include "src/common/camera.h"

#include "src/util/controller_util.h"
#include "src/util/file_util.h"

int main(int argc, char** argv)
{
    // create window
    GLFWwindow* window = initGLFWWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");
    if (!window)
    {
        std::cout << "GLFW initializes failed" << std::endl;
        return EXIT_FAILURE;
    }

    // init glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return EXIT_FAILURE;
    }

    glEnable(GL_DEPTH_TEST);

    Shader shader(getFilePath("vertex.vsh", FileType::FLIETYPE_SHADER).c_str(),
                  getFilePath("fragment.fsh", FileType::FLIETYPE_SHADER).c_str());

    // load models
    std::string path = getFilePath("cyborg/cyborg.obj", FileType::FLIETYPE_MODEL);
    Model testModel(path);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        // render
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(CAMERA.Zoom), (GLfloat)SCR_WIDTH / (GLfloat)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = CAMERA.GetViewMatrix();
        shader.setMat4(STR_PROJECTION, projection);
        shader.setMat4(STR_VIEW, view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setMat4(STR_MODEL, model);
        testModel.Draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}
