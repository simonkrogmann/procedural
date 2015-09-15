#include <iostream>
#include <glm/gtc/constants.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

using namespace gl;

int main() {
    std::cout << glm::pi<double>() << std::endl;

    if (!glfwInit())
        return -1;
    GLFWwindow* window = glfwCreateWindow(640, 480, "glphotomagic", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glbinding::Binding::initialize();
    glClearColor(1.0, 0.0, 0.0, 1.0);

    while (!glfwWindowShouldClose(window))
    {
        // TODO: render
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}
