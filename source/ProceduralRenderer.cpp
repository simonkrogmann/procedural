#include "ProceduralRenderer.h"

#include <glbinding/gl/gl.h>

using namespace gl;

ProceduralRenderer::ProceduralRenderer()
    : screen { }
    , shader { "screenalignedquad.vert", "procedural.frag" }
{

}

ProceduralRenderer::~ProceduralRenderer()
{

}

void ProceduralRenderer::init()
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
}

void ProceduralRenderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    screen.draw();
}
