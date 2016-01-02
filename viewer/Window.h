#pragma once

#include <string>
#include <memory>

#include "Renderer.h"
#include "util.h"

struct GLFWwindow;

class Window {
public:
    Window();
    ~Window();

    void requestGLVersion(const int& major, const int& minor);
    int init(const std::string& title);
    void initAfterGL();
    void setRenderer(std::unique_ptr<Renderer> renderer);
    Renderer * renderer();
    void keyPress(int key, int action, int mods);
    void resize(const unsigned int& width, const unsigned int& height);
    void setFileResolution(const unsigned int& width, const unsigned int& height);
    void loop();
private:
    GLFWwindow * m_window;
    std::unique_ptr<Renderer> m_renderer;
    util::viewport::Viewport m_viewport;
    util::viewport::Viewport m_fileResolution;
};
