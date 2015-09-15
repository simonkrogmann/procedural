#include <iostream>

#include "Window.h"
#include "PhotoRenderer.h"

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

using namespace gl;

int main() {
    Window w;
    auto renderer = std::make_unique<PhotoRenderer>();

    glbinding::Binding::initialize();

    w.init(std::move(renderer), "glphotomagic");
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    w.loop();

    return 0;
}
