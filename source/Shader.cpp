#include "Shader.h"

#include <glbinding/gl/gl.h>
#include <iostream>

#include "util.h"

using namespace gl;

Shader Shader::vertex(const std::string& filename,
        const std::vector<std::string>& includes)
{
    return Shader(filename, util::loadFile(filename), GL_VERTEX_SHADER, includes);
}
Shader Shader::geometry(const std::string& filename,
        const std::vector<std::string>& includes)
{
    return Shader(filename, util::loadFile(filename), GL_GEOMETRY_SHADER, includes);
}
Shader Shader::fragment(const std::string& filename,
        const std::vector<std::string>& includes)
{
    return Shader(filename, util::loadFile(filename), GL_FRAGMENT_SHADER, includes);
}
Shader Shader::compute(const std::string& filename,
        const std::vector<std::string>& includes)
{
    return Shader(filename, util::loadFile(filename), GL_COMPUTE_SHADER, includes);
}

Shader::Shader(const std::string& name, const std::string& source,
    const GLenum& type, const std::vector<std::string>& includes)
: m_name{name}
{
    const std::string includeLocation = "../source/shader/";

    auto shaderSource = source;
    util::replace(shaderSource, "#version 140", "#version " + util::glslVersion());

    // handle includes
    for (auto& include : includes)
    {
        includeShader("/" + include, util::loadFile(includeLocation + include + ".glsl"));
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
    if (util::glExtensionSupported("GL_ARB_shader_include"))
    {
        glNamedStringARB(GL_SHADER_INCLUDE_ARB, util::glLength(name), name.c_str(),
            util::glLength(source), source.c_str());
    }

}

void Shader::compileShader(const std::string& source)
{
    const auto ARBinclude = util::glExtensionSupported("GL_ARB_shader_include");
    auto uploadSource = source;
    if (!ARBinclude) {
        for (const auto& include : m_includes)
        {
            const auto directive = "#include \"" + include.first + "\"";
            util::replace(uploadSource, directive, include.second);
        }
    }
    const auto shaderCString = uploadSource.c_str();
    const auto shaderLength = util::glLength(uploadSource);
    glShaderSource(m_shader, 1, &shaderCString, &shaderLength);
    if (ARBinclude)
    {
        std::vector<const char*> includeCStrings;
        for (const auto& include : m_includes) {
            includeCStrings.push_back(include.first.c_str());
        }
        glCompileShaderIncludeARB(m_shader, util::glLength(includeCStrings),
            includeCStrings.data(), nullptr);
    }
    else
    {
        glCompileShader(m_shader);
    }
}

void Shader::deleteIncludes()
{
    if (util::glExtensionSupported("GL_ARB_shader_include"))
    {
        for (const auto& include : m_includes)
        {
            glDeleteNamedStringARB(util::glLength(include.first), include.first.c_str());
        }
    }
}

Shader::Shader(Shader&& old)
: m_name{old.m_name}
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
    std::cout << "Compilation failed for " << m_name << ":" << std::endl;
    GLint length;
    glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &length);
    char * infoLog = new char[length + 1];
    glGetShaderInfoLog(m_shader, length, NULL, infoLog);
    std::cout << infoLog << std::endl;
    delete[] infoLog;
}
