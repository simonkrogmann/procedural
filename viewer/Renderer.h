#pragma once

#include <chrono>

#include <glbinding/gl/gl.h>
#include <utilgpu/cpp/FileWatcher.h>
#include <utilgpu/gl/Framebuffer.h>

using namespace gl;

namespace util
{
namespace viewport
{
struct Viewport;
}
}

class Renderer
{
public:
    Renderer();
    virtual ~Renderer();

    virtual void init() = 0;
    virtual void reload() = 0;
    void render(const util::viewport::Viewport& viewport);

    void renderOffscreen(const Framebuffer& fbo,
                         const util::viewport::Viewport& resolution);
    void renderToFile(const util::viewport::Viewport& resolution);
    void measureFrameTime();
    void updateFrameTime();
    virtual void saveFramebuffers() = 0;

protected:
    void addDependentPath(const std::string& path);
    virtual void draw(const util::viewport::Viewport& viewport) = 0;

private:
    Framebuffer m_fileFBO;
    util::FileWatcher m_fileWatcher;

    unsigned int m_frames = 0;
    bool m_measureFrameTime = false;
    std::chrono::time_point<std::chrono::steady_clock> m_start;
};
