#include "Window.h"

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
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}