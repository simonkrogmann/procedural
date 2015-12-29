#pragma once

#include <glbinding/gl/gl.h>

#include "Framebuffer.h"

using namespace gl;

namespace util
{
    struct Viewport;
}

class Renderer {
public:
    Renderer();
    virtual ~Renderer();

    virtual void init() = 0;
    virtual void render(const util::Viewport& viewport) = 0;
    virtual void reload() = 0;

    void renderOffscreen(const Framebuffer& fbo, const util::Viewport& resolution);
    void renderToFile(const util::Viewport& resolution);
protected:
    Framebuffer m_fileFBO;
};
