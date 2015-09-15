#include <iostream>
#include <glm/gtc/constants.hpp>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#include "Window.h"

using namespace gl;


int main() {
    Window w;

    w.init("glphotomagic");

    glbinding::Binding::initialize();
    glClearColor(1.0, 0.0, 0.0, 1.0);
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    w.loop();

    return 0;

}
