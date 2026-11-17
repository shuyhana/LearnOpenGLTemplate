#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

extern float deltaTime;
extern float lastFrame;

extern void processInput(GLFWwindow* window);

extern void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

extern void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
