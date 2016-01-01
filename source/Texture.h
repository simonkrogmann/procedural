#pragma once

#include <string>

#include <glbinding/gl/gl.h>

using namespace gl;

class Texture
{
public:
    Texture(const std::string& name, const std::string& filename);
    Texture(Texture&& old);
    Texture(const Texture&) = delete;
    ~Texture();

    void bind() const;
    void load();
    GLuint get() const { return m_texture; }
    std::string name() const { return m_name; }
private:
    std::string m_name;
    std::string m_filename;
    GLuint m_texture;
};
