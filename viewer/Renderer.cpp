#include "Renderer.h"

#include <glbinding/gl/gl.h>

#include <utilpp/gl/viewport.h>

using namespace gl;

Renderer::Renderer() : m_fileFBO{1920, 1080}, m_fileWatcher{}
{
}

Renderer::~Renderer()
{
}

void Renderer::render(const util::viewport::Viewport& viewport)
{
    if (m_fileWatcher.check())
    {
        reload();
    }
    draw(viewport);
}

void Renderer::renderToFile(const util::viewport::Viewport& resolution)
{
    m_fileFBO.resize(resolution.width, resolution.height);
    renderOffscreen(m_fileFBO, resolution);
    m_fileFBO.save("test.png");
}

void Renderer::renderOffscreen(const Framebuffer& fbo,
                               const util::viewport::Viewport& resolution)
{
    const auto keeper = util::viewport::use(resolution);
    const auto keeper2 = fbo.use(GL_DRAW_FRAMEBUFFER);

    render(resolution);
}

void Renderer::addDependentPath(const std::string& path)
{
    m_fileWatcher.addFile(path);
}
