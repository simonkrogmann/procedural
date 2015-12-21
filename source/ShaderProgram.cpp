#include "ShaderProgram.h"

#include <glbinding/gl/gl.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

using namespace gl;

ShaderProgram::ShaderProgram() {}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(program);
}

GLuint ShaderProgram::createShader(const std::string& fileName, GLenum type) {
    GLuint shader = glCreateShader(type);
    std::ifstream sourceFile;

    sourceFile.open(fileName);
    std::stringstream sourceBuffer;
    sourceBuffer << sourceFile.rdbuf();
    std::string sourceString = sourceBuffer.str();
    sourceFile.close();

    const char * source = sourceString.c_str();

    auto length = static_cast<GLint>(sourceString.length());
    glShaderSource(shader, 1, &source, &length);
    glCompileShader(shader);
    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if ((GLboolean) isCompiled == GL_FALSE) {
        std::cout << "Compilation failed for " << fileName << std::endl;
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char * infoLog = new char[length + 1];
        glGetShaderInfoLog(shader, length, NULL, infoLog);
        std::cout << infoLog << std::endl;
        delete[] infoLog;
        return 0;
    }
    return shader;
}

ShaderProgram::ShaderProgram(const std::string& vertFileName, const std::string& fragFileName) {
    std::vector<GLuint> shaders;

    shaders.push_back(createShader(vertFileName, GL_VERTEX_SHADER));
    shaders.push_back(createShader(fragFileName, GL_FRAGMENT_SHADER));

    program = linkShaders(shaders);

    if (!isLinked()) {
        printLinkingError();
    }
}

ShaderProgram::ShaderProgram(const std::string& vertFileName, const std::string& geomFileName, const std::string& fragFileName) {
    std::vector<GLuint> shaders;

    shaders.push_back(createShader(vertFileName, GL_VERTEX_SHADER));
    shaders.push_back(createShader(geomFileName, GL_GEOMETRY_SHADER));
    shaders.push_back(createShader(fragFileName, GL_FRAGMENT_SHADER));

    program = linkShaders(shaders);

    if (!isLinked()) {
        printLinkingError();
    }
}

ShaderProgram::ShaderProgram(const std::string& compFileName) {
    std::vector<GLuint> shaders;

    shaders.push_back(createShader(compFileName, GL_COMPUTE_SHADER));

    program = linkShaders(shaders);

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



bool ShaderProgram::isLinked() {
    GLint isLinked;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    return (GLboolean) isLinked != GL_FALSE;
}

void ShaderProgram::printLinkingError() {
    std::cout << "Linking Failed" << std::endl;
    GLint length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
    char * infoLog = new char[length + 1];
    glGetProgramInfoLog(program, length, NULL, infoLog);
    std::cout << infoLog << std::endl;
    delete[] infoLog;
}

void ShaderProgram::use() {
    glUseProgram(program);
}

GLint ShaderProgram::getUniformLocation(const char * uniformName) {
    return glGetUniformLocation(program, uniformName);
}
