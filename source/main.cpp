#include <iostream>

#include "Window.h"
#include "ProceduralRenderer.h"

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

using namespace gl;

int main() {
    Window w;
    w.init("procedural");

    glbinding::Binding::initialize();
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    auto renderer = std::make_unique<ProceduralRenderer>();

    w.setRenderer(std::move(renderer));
    w.loop();

    return 0;
}
