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

    template<typename T>
    GLint glLength(T object) {
        return static_cast<GLint>(object.size());
    }

    bool glExtensionSupported(std::string extension)
    {
        std::string extensions = reinterpret_cast<char const *>(glGetString(GL_EXTENSIONS));
        return extensions.find(extension) != std::string::npos;
    }

    void replace(std::string& target, const std::string& old, const std::string& with)
    {
        const auto position = target.find(old);
        target.replace(position, old.length(), with);
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

    const auto shaderSource = load_file(shaderLocation + filename);

    // handle includes
    for (auto& include : includes)
    {
        includeShader("/" + include, load_file(shaderLocation + include + ".glsl"));
    }

    m_shader = glCreateShader(type);
    compileShader(shaderSource);
    if (!isCompiled())
    {
        printCompilationError();
    }

    deleteIncludes();
}

void Shader::includeShader(const std::string& name, const std::string& source)
{
    m_includes[name] = source;
    if (glExtensionSupported("GL_ARB_shader_include"))
    {
        glNamedStringARB(GL_SHADER_INCLUDE_ARB, glLength(name), name.c_str(),
            glLength(source), source.c_str());
    }

}

void Shader::compileShader(const std::string& source)
{
    const auto ARBinclude = glExtensionSupported("GL_ARB_shader_include");
    auto uploadSource = source;
    if (!ARBinclude) {
        for (const auto& include : m_includes)
        {
            const auto directive = "#include \"" + include.first + "\"";
            replace(uploadSource, directive, include.second);
        }
    }
    const auto shaderCString = uploadSource.c_str();
    const auto shaderLength = glLength(uploadSource);
    glShaderSource(m_shader, 1, &shaderCString, &shaderLength);
    if (ARBinclude)
    {
        std::vector<const char*> includeCStrings;
        for (const auto& include : m_includes) {
            includeCStrings.push_back(include.first.c_str());
        }
        glCompileShaderIncludeARB(m_shader, glLength(includeCStrings),
            includeCStrings.data(), nullptr);
    }
    else
    {
        glCompileShader(m_shader);
    }
}

void Shader::deleteIncludes()
{
    if (glExtensionSupported("GL_ARB_shader_include"))
    {
        for (const auto& include : m_includes)
        {
            glDeleteNamedStringARB(glLength(include.first), include.first.c_str());
        }
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
