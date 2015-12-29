#include "Window.h"

#include <map>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glbinding/gl/gl.h>

namespace
{
    using namespace gl;

    std::map<GLFWwindow*, Window*> windows;

    void onResize(GLFWwindow* window, int width, int height)
    {
        windows[window]->resize(width, height);
    }

    void onKeyPress(GLFWwindow* window, int key, int, int action, int mods)
    {
        windows[window]->keyPress(key, action, mods);
    }

}


Window::Window()
: m_window{ nullptr }
{
    glfwInit();
}

Window::~Window()
{
    if (m_window != nullptr)
    {
        glfwTerminate();
        windows.erase(m_window);
    }
}

void Window::requestGLVersion(int major, int minor)
{

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}

int Window::init(std::string title)
{
    auto window = glfwCreateWindow(640, 480, title.c_str(), NULL, NULL);
    m_viewport = util::Viewport {0, 0, 640, 480};

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    m_window = window;
    windows[m_window] = this;

    return 0;
}

void Window::initAfterGL()
{
    glfwSetWindowSizeCallback(m_window, onResize);
    glfwSetKeyCallback(m_window, onKeyPress);
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

void Window::keyPress(int key, int action, int mods)
{
    if (key == 'R' && action == GLFW_PRESS && mods == 0)
    {
        m_renderer->reload();
    }
}

void Window::resize(int width, int height)
{
    m_viewport = util::Viewport {0, 0, width, height};
    util::setViewport(m_viewport);
}

void Window::loop()
{
    while (!glfwWindowShouldClose(m_window))
    {
        m_renderer->render(m_viewport);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}
