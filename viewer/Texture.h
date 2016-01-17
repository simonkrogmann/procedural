#pragma once

#include <string>

#include <glbinding/gl/gl.h>
#include <utilgpu/cpp/file.h>

using namespace gl;

class Texture
{
public:
    Texture(const util::File& file);
    Texture(Texture&& old);
    Texture(const Texture&) = delete;
    ~Texture();

    void bind() const;
    void load();
    GLuint get() const { return m_texture; }
    std::string name() const { return m_file.name; }
private:
    util::File m_file;
    GLuint m_texture;
};
