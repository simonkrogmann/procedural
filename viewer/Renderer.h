#pragma once

#include <glbinding/gl/gl.h>

#include "Framebuffer.h"
#include "FileWatcher.h"

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

protected:
    void addDependentPath(const std::string& path);
    virtual void draw(const util::viewport::Viewport& viewport) = 0;

private:
    Framebuffer m_fileFBO;
    FileWatcher m_fileWatcher;
};
