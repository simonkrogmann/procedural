#pragma once

#include <glbinding/gl/gl.h>

#include "Framebuffer.h"

using namespace gl;

namespace util
{
    namespace viewport {
        struct Viewport;
    }
}

class Renderer {
public:
    Renderer();
    virtual ~Renderer();

    virtual void init() = 0;
    virtual void render(const util::viewport::Viewport& viewport) = 0;
    virtual void reload() = 0;

    void renderOffscreen(const Framebuffer& fbo, const util::viewport::Viewport& resolution);
    void renderToFile(const util::viewport::Viewport& resolution);
protected:
    Framebuffer m_fileFBO;
};
