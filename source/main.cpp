#include <iostream>

#include "Window.h"
#include "PhotoRenderer.h"

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

using namespace gl;

int main() {
    Window w;
    w.init("glphotomagic");

    glbinding::Binding::initialize();

    auto renderer = std::make_unique<PhotoRenderer>();

    w.setRenderer(std::move(renderer));
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    w.loop();

    return 0;
}
