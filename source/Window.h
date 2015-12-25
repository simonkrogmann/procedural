#pragma once

#include <string>
#include <memory>

#include "Renderer.h"

struct GLFWwindow;

class Window {
public:
    Window();
    ~Window();

    int init(std::string title);
    void initGL();
    void setRenderer(std::unique_ptr<Renderer> renderer);
    Renderer * renderer();
    void keyPress(int key, int action, int mods);
    void loop();
private:
    GLFWwindow * m_window;
    std::unique_ptr<Renderer> m_renderer;
};
