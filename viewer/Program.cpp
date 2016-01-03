#include "Program.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

#include <glbinding/gl/gl.h>

#include "Shader.h"
#include "util.h"

using namespace gl;

Program::Program(const util::Group<Shader>& shaders) : m_program{0}
{
    m_program = linkShaders(shaders);

    if (!isLinked())
    {
        printLinkingError();
    }
}

Program::Program(Program&& old) : m_program{old.m_program}
{
    old.m_program = 0;
}

Program::~Program()
{
    glDeleteProgram(m_program);
}

GLuint Program::linkShaders(const util::Group<Shader>& shaders)
{
    GLuint linkProgram = glCreateProgram();

    for (const auto& shader : shaders)
    {
        glAttachShader(linkProgram, shader.get());
    }

    glLinkProgram(linkProgram);

    for (const auto& shader : shaders)
    {
        glDetachShader(linkProgram, shader.get());
    }

    return linkProgram;
}

bool Program::isLinked() const
{
    GLint isLinked;
    glGetProgramiv(m_program, GL_LINK_STATUS, &isLinked);
    return static_cast<GLboolean>(isLinked) != GL_FALSE;
}

void Program::printLinkingError() const
{
    std::cout << "Linking failed:" << std::endl;
    GLint length;
    glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);
    char* infoLog = new char[length + 1];
    glGetProgramInfoLog(m_program, length, NULL, infoLog);
    std::cout << infoLog << std::endl;
    delete[] infoLog;
}

void Program::use() const
{
    glUseProgram(m_program);
}

GLint Program::getUniformLocation(const std::string& uniformName) const
{
    return glGetUniformLocation(m_program, uniformName.c_str());
}

GLint Program::operator[](const std::string& uniformName) const
{
    return getUniformLocation(uniformName);
}
