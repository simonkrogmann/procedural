#pragma once
#include <string>
#include <glbinding/gl/gl.h>
#include <vector>


using namespace gl;

class Shader
{
public:
    static Shader vertex(const std::string& filename);
    static Shader geometry(const std::string& filename);
    static Shader fragment(const std::string& filename);
    static Shader compute(const std::string& filename);
    Shader();
    Shader(Shader&& old);
    Shader(const Shader&) = delete;
    Shader(const std::string& filename, const GLenum& type);
    ~Shader();

    bool isCompiled() const;
    void printCompilationError() const;
    GLuint get() const { return m_shader; }
private:
    std::string m_filename;
    GLuint m_shader;
};
