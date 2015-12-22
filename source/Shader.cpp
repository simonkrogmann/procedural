#include "Shader.h"

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

Shader Shader::vertex(const std::string& filename)
{
    return Shader(filename, GL_VERTEX_SHADER);
}
Shader Shader::geometry(const std::string& filename)
{
    return Shader(filename, GL_GEOMETRY_SHADER);
}
Shader Shader::fragment(const std::string& filename)
{
    return Shader(filename, GL_FRAGMENT_SHADER);
}
Shader Shader::compute(const std::string& filename)
{
    return Shader(filename, GL_COMPUTE_SHADER);
}

Shader::Shader(const std::string& filename, const GLenum& type)
: m_filename{filename}
{
    const std::string shaderLocation = "../source/shader/";

    const auto sourceString = load_file(shaderLocation + filename);
    const auto source = sourceString.c_str();
    const auto length = static_cast<GLint>(sourceString.length());

    m_shader = glCreateShader(type);
    glShaderSource(m_shader, 1, &source, &length);
    glCompileShader(m_shader);
    if (!isCompiled())
    {
        printCompilationError();
    }
}

Shader::Shader(Shader&& old)
: m_filename{old.m_filename}
, m_shader{old.m_shader}
{
    old.m_shader = 0;
}

Shader::~Shader()
{
    glDeleteShader(m_shader);
}

bool Shader::isCompiled() const
{
    GLint isCompiled;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &isCompiled);
    return (GLboolean) isCompiled != GL_FALSE;
}

void Shader::printCompilationError() const
{
    std::cout << "Compilation failed for " << m_filename << ":" << std::endl;
    GLint length;
    glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &length);
    char * infoLog = new char[length + 1];
    glGetShaderInfoLog(m_shader, length, NULL, infoLog);
    std::cout << infoLog << std::endl;
    delete[] infoLog;
}
