#include "ProceduralRenderer.h"

#include <glbinding/gl/gl.h>

using namespace gl;

#include "Shader.h"
#include "Group.h"

ProceduralRenderer::ProceduralRenderer()
    : m_screen { }
    , m_program { Group<Shader>(
        Shader::vertex("screenalignedquad.vert"),
        Shader::fragment("procedural.frag")
    )}
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

    m_program.use();
    m_screen.draw();
}
