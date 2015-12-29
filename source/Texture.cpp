#include "Texture.h"

#include <glbinding/gl/gl.h>

#include "util.h"

using namespace gl;

Texture::Texture(const std::string& name, const std::string& filename)
: m_name {name}
, m_filename {filename}
, m_texture {0}
{
    glGenTextures(1, &m_texture);
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint) GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint) GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint) GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint) GL_LINEAR);
}

Texture::~Texture()
{

}

Texture::Texture(Texture&& old)
: m_name {old.m_name}
, m_filename {old.m_filename}
, m_texture {old.m_texture}
{
    old.m_texture = 0;
}

void Texture::load()
{
    auto glImage = util::loadImage(m_filename);
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, (GLint) GL_RGBA8, glImage.width(),
        glImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, glImage.constBits());
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
