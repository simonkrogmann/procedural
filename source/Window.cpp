#include "Window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glbinding/gl/gl.h>

namespace
{
    using namespace gl;

    void onResize(GLFWwindow*, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}


Window::Window()
: m_window{ nullptr }
{

}

int Window::init(std::string title)
{
    if (!glfwInit())
    {
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    auto window = glfwCreateWindow(640, 480, title.c_str(), NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    m_window = window;

    return 0;
}

void Window::initGL()
{
    glfwSetWindowSizeCallback(m_window, onResize);
}

Window::~Window()
{
    if (m_window != nullptr)
    {
        glfwTerminate();
    }
}

void Window::setRenderer(std::unique_ptr<Renderer> renderer)
{
    m_renderer = std::move(renderer);
    m_renderer->init();
}

Renderer * Window::renderer()
{
    return m_renderer.get();
}

void Window::loop()
{
    while (!glfwWindowShouldClose(m_window))
    {
        m_renderer->render();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}
