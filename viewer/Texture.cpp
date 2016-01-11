#include "Texture.h"

#include <glbinding/gl/gl.h>

#include <utilpp/file.h>

using namespace gl;

Texture::Texture(const util::File& file) : m_file{file}, m_texture{0}
{
    glGenTextures(1, &m_texture);
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    static_cast<GLint>(GL_REPEAT));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                    static_cast<GLint>(GL_REPEAT));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    static_cast<GLint>(GL_LINEAR));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    static_cast<GLint>(GL_LINEAR));
}

Texture::~Texture()
{
}

Texture::Texture(Texture&& old) : m_file{old.m_file}, m_texture{old.m_texture}
{
    old.m_texture = 0;
}

void Texture::load()
{
    const auto glImage = util::loadImage(m_file.path);
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(GL_RGBA8),
                 glImage.width(), glImage.height(), 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, glImage.constBits());
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
