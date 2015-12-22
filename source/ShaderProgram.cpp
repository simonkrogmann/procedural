#include "ShaderProgram.h"

#include <glbinding/gl/gl.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

using namespace gl;

namespace
{
    std::string load_file(std::string filename)
    {
        std::ifstream sourceFile(filename);

        std::stringstream sourceBuffer;
        sourceBuffer << sourceFile.rdbuf();
        return sourceBuffer.str();
    }
}

ShaderProgram::ShaderProgram() {}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_program);
}

GLuint ShaderProgram::createShader(const std::string& filename, GLenum type) {
    GLuint shader = glCreateShader(type);
    const std::string shaderLocation = "../source/shader/";

    const auto sourceString = load_file(shaderLocation + filename);
    const auto source = sourceString.c_str();

    auto length = static_cast<GLint>(sourceString.length());
    glShaderSource(shader, 1, &source, &length);
    glCompileShader(shader);
    if (!isCompiled(shader)) {
        printCompilationError(shader, filename);
        return 0;
    }
    return shader;
}

ShaderProgram::ShaderProgram(const std::string& vertFilename, const std::string& fragFilename) {
    std::vector<GLuint> shaders;

    shaders.push_back(createShader(vertFilename, GL_VERTEX_SHADER));
    shaders.push_back(createShader(fragFilename, GL_FRAGMENT_SHADER));

    m_program = linkShaders(shaders);

    if (!isLinked()) {
        printLinkingError();
    }
}

ShaderProgram::ShaderProgram(const std::string& vertFilename, const std::string& geomFilename, const std::string& fragFilename) {
    std::vector<GLuint> shaders;

    shaders.push_back(createShader(vertFilename, GL_VERTEX_SHADER));
    shaders.push_back(createShader(geomFilename, GL_GEOMETRY_SHADER));
    shaders.push_back(createShader(fragFilename, GL_FRAGMENT_SHADER));

    m_program = linkShaders(shaders);

    if (!isLinked()) {
        printLinkingError();
    }
}

ShaderProgram::ShaderProgram(const std::string& compFilename) {
    std::vector<GLuint> shaders;

    shaders.push_back(createShader(compFilename, GL_COMPUTE_SHADER));

    m_program = linkShaders(shaders);

    if (!isLinked()) {
        printLinkingError();
    }
}

GLuint ShaderProgram::linkShaders(const std::vector<GLuint>& shaders) {
    GLuint linkProgram = glCreateProgram();

    for (GLuint shader : shaders) {
        glAttachShader(linkProgram, shader);
    }

    glLinkProgram(linkProgram);


    for (GLuint shader : shaders) {
        glDetachShader(linkProgram, shader);
        glDeleteShader(shader);
    }

    return linkProgram;
}

bool ShaderProgram::isCompiled(const GLuint& shader)
{
    GLint isCompiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    return (GLboolean) isCompiled != GL_FALSE;
}

bool ShaderProgram::isLinked()
{
    GLint isLinked;
    glGetProgramiv(m_program, GL_LINK_STATUS, &isLinked);
    return (GLboolean) isLinked != GL_FALSE;
}

void ShaderProgram::printLinkingError()
{
    std::cout << "Linking failed" << std::endl;
    GLint length;
    glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);
    char * infoLog = new char[length + 1];
    glGetProgramInfoLog(m_program, length, NULL, infoLog);
    std::cout << infoLog << std::endl;
    delete[] infoLog;
}

void ShaderProgram::printCompilationError(const GLuint& shader, const std::string& filename)
{
    std::cout << "Compilation failed for " << filename << ":" << std::endl;
    GLint length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    char * infoLog = new char[length + 1];
    glGetShaderInfoLog(shader, length, NULL, infoLog);
    std::cout << infoLog << std::endl;
    delete[] infoLog;
}

void ShaderProgram::use()
{
    glUseProgram(m_program);
}

GLint ShaderProgram::getUniformLocation(const char* uniformName)
{
    return glGetUniformLocation(m_program, uniformName);
}
