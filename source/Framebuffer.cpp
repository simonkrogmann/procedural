#include "Framebuffer.h"

#include <iostream>

#include <glbinding/gl/gl.h>

#include "convert.h"

using namespace gl;

Framebuffer::Framebuffer(const unsigned int& width, const unsigned int& height)
: m_framebuffer {0}
, m_color {0}
, m_depth {0}
, m_width {0}
, m_height {0}
{
    glGenFramebuffers(1, &m_framebuffer);
    glGenTextures(1, &m_color);

    glBindTexture(GL_TEXTURE_2D, m_color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint) GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint) GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint) GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint) GL_NEAREST);

    glGenRenderbuffers(1, &m_depth);

    resize(width, height);

    auto keeper = use();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth);

    auto framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (framebufferStatus != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Framebuffer is incomplete: " << framebufferStatus << std::endl;
    }
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &m_framebuffer);
    glDeleteRenderbuffers(1, &m_color);
    glDeleteRenderbuffers(1, &m_depth);
}

Framebuffer::Framebuffer(Framebuffer&& old)
: m_framebuffer {old.m_framebuffer}
{
    old.m_framebuffer = 0;
}


util::StateKeeper Framebuffer::use(GLenum mode) const
{
    auto old = util::glGetInteger(GL_FRAMEBUFFER_BINDING);
    glBindFramebuffer(mode, m_framebuffer);
    return { [=]() { glBindFramebuffer(mode, old); } };
}

void Framebuffer::save(std::string filename)
{
    auto keeper = use(GL_READ_FRAMEBUFFER);
    std::vector<unsigned char> imageData (m_width * m_height * 4);
    glReadPixels(0, 0, m_width, m_height, GL_BGRA, GL_UNSIGNED_BYTE, &imageData[0]);
    saveImage(imageData, m_width, m_height, filename);
}

void Framebuffer::resize(const unsigned int& width, const unsigned int& height)
{
    if (m_width == width && m_height == height)
    {
        return;
    }
    m_width = width;
    m_height = height;

    glBindTexture(GL_TEXTURE_2D, m_color);
    glTexImage2D(GL_TEXTURE_2D, 0, (GLint) GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, m_depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
