#pragma once
#include <string>
#include <glbinding/gl/gl.h>
#include <vector>

using namespace gl;

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();
    ShaderProgram(const std::string& vertFileName, const std::string& fragFileName);
    ShaderProgram(const std::string& vertFileName, const std::string& geomFileName, const std::string& fragFileName);
    ShaderProgram(const std::string& compFileName);

    bool isLinked();
    void printLinkingError();
    GLint getUniformLocation(const char * uniformName);
    GLuint getProgram() { return m_program; };
    void use();
private:
    bool isCompiled(const GLuint& shader);
    void printCompilationError(const GLuint& shader, const std::string& filename);
    GLuint createShader(const std::string& fileName, GLenum type);
    GLuint linkShaders(const std::vector<GLuint>& shaders);

    GLuint m_program;
};
