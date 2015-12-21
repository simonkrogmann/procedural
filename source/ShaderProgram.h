#pragma once
#include <string>
#include <glbinding/gl/gl.h>
#include <vector>

using namespace gl;

class ShaderProgram {
private:
    GLuint createShader(const std::string& fileName, GLenum type);
    GLuint linkShaders(const std::vector<GLuint>& shaders);

    GLuint program;
public:
    ShaderProgram();
    ~ShaderProgram();
    ShaderProgram(const std::string& vertFileName, const std::string& fragFileName);
    ShaderProgram(const std::string& vertFileName, const std::string& geomFileName, const std::string& fragFileName);
    ShaderProgram(const std::string& compFileName);

    bool isLinked();
    void printLinkingError();
    GLint getUniformLocation(const char * uniformName);
    GLuint getProgram() { return program; };
    void use();
};
