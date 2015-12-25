#include "ProceduralRenderer.h"

#include <glbinding/gl/gl.h>

#include "Shader.h"
#include "Group.h"

using namespace gl;

ProceduralRenderer::ProceduralRenderer(const std::vector<std::string>& includes)
    : Renderer { }
    , m_screen { }
    , m_program { }
    , m_includes { includes }
{

}

ProceduralRenderer::~ProceduralRenderer()
{

}

void ProceduralRenderer::init()
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
    recompile();
}

void ProceduralRenderer::recompile()
{
    Group<Shader> shaders (
        Shader::vertex("screenalignedquad.vert"),
        Shader::fragment("procedural.frag", m_includes)
    );

    m_program = std::make_unique<Program>(shaders);
}


void ProceduralRenderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->use();
    auto loc = m_program->getUniformLocation("windowSize");
    GLint data[4];
    glGetIntegerv(GL_VIEWPORT, data);
    glUniform2i(loc, data[2], data[3]);
    m_screen.draw();
}
