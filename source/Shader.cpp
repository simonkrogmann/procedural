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

Shader Shader::vertex(const std::string& filename,
        const std::vector<std::string>& includes)
{
    return Shader(filename, GL_VERTEX_SHADER, includes);
}
Shader Shader::geometry(const std::string& filename,
        const std::vector<std::string>& includes)
{
    return Shader(filename, GL_GEOMETRY_SHADER, includes);
}
Shader Shader::fragment(const std::string& filename,
        const std::vector<std::string>& includes)
{
    return Shader(filename, GL_FRAGMENT_SHADER, includes);
}
Shader Shader::compute(const std::string& filename,
        const std::vector<std::string>& includes)
{
    return Shader(filename, GL_COMPUTE_SHADER, includes);
}

Shader::Shader(const std::string& filename, const GLenum& type,
        const std::vector<std::string>& includes)
: m_filename{filename}
{
    const std::string shaderLocation = "../source/shader/";

    auto glLength = [](auto string) {
        return static_cast<GLint>(string.size());
    };

    const auto shaderSource = load_file(shaderLocation + filename);
    const auto shaderCString = shaderSource.c_str();
    const auto shaderLength = glLength(shaderSource);

    // handle includes
    std::vector<const char *> includeCStrings;
    for (auto& include : includes)
    {
        const auto name = "/" + include;
        includeCStrings.push_back(name.c_str());
        const auto includeSource = load_file(shaderLocation + include + ".glsl");
        glNamedStringARB(GL_SHADER_INCLUDE_ARB, glLength(name), name.c_str(),
            glLength(includeSource), includeSource.c_str());
    }

    m_shader = glCreateShader(type);
    glShaderSource(m_shader, 1, &shaderCString, &shaderLength);
    glCompileShaderIncludeARB(m_shader, glLength(includeCStrings),
        includeCStrings.data(), nullptr);
    if (!isCompiled())
    {
        printCompilationError();
    }

    // delte includes
    for (auto& include : includes)
    {
        const auto name = "/" + include;
        glDeleteNamedStringARB(glLength(name), name.c_str());
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
