#include "Renderer.h"

#include <glbinding/gl/gl.h>

#include "util.h"

using namespace gl;

Renderer::Renderer()
: m_fileFBO {1920, 1080}
{

}

Renderer::~Renderer()
{

}

void Renderer::renderToFile(const util::Viewport& resolution)
{
    const int width = resolution.width, height = resolution.height;
    m_fileFBO.resize(width, height);
    renderOffscreen(m_fileFBO, resolution);
    m_fileFBO.save("test.png");
}

void Renderer::renderOffscreen(const Framebuffer& fbo, const util::Viewport& resolution)
{
    auto old = util::viewport();

    fbo.bind();
    util::setViewport(resolution);
    render(resolution);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    util::setViewport(old);
}
