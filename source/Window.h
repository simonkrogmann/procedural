#pragma once

#include <string>
#include <memory>

#include "Renderer.h"

struct GLFWwindow;

class Window {
public:
    Window();
    ~Window();

    int init(std::unique_ptr<Renderer> renderer, std::string title);
    void loop();
private:
    GLFWwindow * m_window;
    std::unique_ptr<Renderer> m_renderer;
};
