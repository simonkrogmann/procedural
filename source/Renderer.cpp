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

void Renderer::renderToFile(const util::viewport::Viewport& resolution)
{
    m_fileFBO.resize(resolution.width, resolution.height);
    renderOffscreen(m_fileFBO, resolution);
    m_fileFBO.save("test.png");
}

void Renderer::renderOffscreen(const Framebuffer& fbo, const util::viewport::Viewport& resolution)
{
    auto keeper = util::viewport::use(resolution);
    auto keeper2 = fbo.use(GL_DRAW_FRAMEBUFFER);

    render(resolution);
}
