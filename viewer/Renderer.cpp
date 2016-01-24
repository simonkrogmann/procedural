#include "Renderer.h"

#include <iostream>

#include <glbinding/gl/gl.h>
#include <utilgpu/gl/viewport.h>

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
    if (m_measureFrameTime)
    {
        updateFrameTime();
    }
}

void Renderer::updateFrameTime()
{
    std::chrono::duration<double> diff =
        std::chrono::steady_clock::now() - m_start;
    if (diff.count() > 1.0)
    {
        std::cout << 1000.0 / m_frames << " ms/frame" << std::endl;
        m_measureFrameTime = false;
    }
    ++m_frames;
}

void Renderer::measureFrameTime()
{
    m_frames = 0;
    m_measureFrameTime = true;
    m_start = std::chrono::steady_clock::now();
}

void Renderer::renderToFile(const util::viewport::Viewport& resolution)
{
    m_fileFBO.resize(resolution.width, resolution.height);
    renderOffscreen(m_fileFBO, resolution);
    m_fileFBO.save("final.png");
    saveFramebuffers();
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
