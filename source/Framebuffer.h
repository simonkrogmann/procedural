#pragma once

#include <string>

#include <glbinding/gl/gl.h>

#include "util.h"

using namespace gl;

class Framebuffer
{
public:
    Framebuffer(const unsigned int& m_width, const unsigned int& height);
    Framebuffer(Framebuffer&& old);
    Framebuffer(const Framebuffer&) = delete;
    ~Framebuffer();

    util::StateKeeper use(GLenum mode = GL_FRAMEBUFFER) const;
    void resize(const unsigned int& m_width, const unsigned int& height);
    void save(std::string filename);

    GLuint get() const { return m_framebuffer; }
private:
    GLuint m_framebuffer;
    GLuint m_color;
    GLuint m_depth;
    unsigned int m_width;
    unsigned int m_height;
};
