#include "PhotoRenderer.h"

#include <glbinding/gl/gl.h>

using namespace gl;

PhotoRenderer::PhotoRenderer()
    : screen { }
    , shader { "../source/shader/simple.vert", "../source/shader/simple.frag" }
{

}

PhotoRenderer::~PhotoRenderer()
{

}

void PhotoRenderer::init()
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
}

void PhotoRenderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    screen.draw();
}
