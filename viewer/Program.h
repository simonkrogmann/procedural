#pragma once

#include <string>

#include <glbinding/gl/gl.h>

using namespace gl;

class Shader;
namespace util
{
    template<typename T> class Group;
}

class Program
{
public:
    Program(const util::Group<Shader>& shaders);
    Program(Program&& old);
    Program(const Program&) = delete;
    ~Program();

    bool isLinked() const;
    void printLinkingError() const;
    GLint getUniformLocation(const std::string& uniformName) const;
    GLint operator[](const std::string& uniformName) const;
    GLuint get() const { return m_program; };
    void use() const;
private:
    GLuint linkShaders(const util::Group<Shader>& shaders);

    GLuint m_program;
};
