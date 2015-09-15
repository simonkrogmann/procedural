#include "Window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

Window::Window()
: m_window{ nullptr }
{

}

int Window::init(std::unique_ptr<Renderer> renderer, std::string title)
{
    if (!glfwInit())
    {
        return -1;
    }

    auto window = glfwCreateWindow(640, 480, title.c_str(), NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    m_window = window;

    m_renderer = std::move(renderer);
    m_renderer->init();

    return 0;
}

Window::~Window()
{
    if (m_window != nullptr)
    {
        glfwTerminate();
    }
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
