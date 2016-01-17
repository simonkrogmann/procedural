#include "Shader.h"

#include <iostream>

#include <glbinding/gl/gl.h>
#include <utilgpu/gl/base.h>
#include <utilgpu/cpp/file.h>
#include <utilgpu/cpp/str.h>

using namespace gl;

unsigned int Shader::id = 0;
std::string Shader::uniqueId()
{
    return std::to_string(++id);
}

std::string Shader::includeString(const std::string& name)
{
    return "#include \"/" + name + "\"\n";
}

std::string Shader::textureString(const std::string& name)
{
    return "uniform sampler2D " + name + ";\n";
}

std::string Shader::idString()
{
    return "const int shader_id = " + uniqueId() + ";\n";
}

Shader Shader::vertex(const util::File& file,
                      const std::vector<util::File>& includes)
{
    return Shader(file.name, file.content(), GL_VERTEX_SHADER, includes);
}

Shader Shader::geometry(const util::File& file,
                        const std::vector<util::File>& includes)
{
    return Shader(file.name, file.content(), GL_GEOMETRY_SHADER, includes);
}

Shader Shader::fragment(const util::File& file,
                        const std::vector<util::File>& includes)
{
    return Shader(file.name, file.content(), GL_FRAGMENT_SHADER, includes);
}

Shader Shader::compute(const util::File& file,
                       const std::vector<util::File>& includes)
{
    return Shader(file.name, file.content(), GL_COMPUTE_SHADER, includes);
}

bool Shader::ARBIncludeSupported()
{
    static auto supported =
        util::glExtensionSupported("GL_ARB_shading_language_include");
    static auto checked = false;
    if (!checked)
    {
        checked = true;
        if (!supported)
        {
            std::cout << "Warning: GL_ARB_shader_include is not supported. "
                      << "The behaviour will be emulated instead." << std::endl;
        }
    }
    return supported;
}

Shader::Shader(const std::string& name, const std::string& source,
               const GLenum& type, const std::vector<util::File>& includes)
    : m_name{name}, m_shader{0}
{
    auto shaderSource = source;
    const static auto glslVersion = util::glslVersion();
    util::replace(shaderSource, "#version 140", "#version " + glslVersion);

    if (util::contains(shaderSource, "//id"))
    {
        const auto idReplacement = (includes.size() > 0) ? idString() : "";
        util::replace(shaderSource, "//id", idReplacement);
    }

    // handle includes
    for (const auto& include : includes)
    {
        includeShader("/" + include.name, include.content());
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
    if (ARBIncludeSupported())
    {
        glNamedStringARB(GL_SHADER_INCLUDE_ARB, util::glLength(name),
                         name.c_str(), util::glLength(source), source.c_str());
    }
}

void Shader::compileShader(const std::string& source)
{
    auto uploadSource = source;
    if (!ARBIncludeSupported())
    {
        for (const auto& include : m_includes)
        {
            const auto directive = "#include \"" + include.first + "\"";
            util::replace(uploadSource, directive, include.second);
        }
    }
    const auto shaderCString = uploadSource.c_str();
    const auto shaderLength = util::glLength(uploadSource);
    glShaderSource(m_shader, 1, &shaderCString, &shaderLength);
    if (ARBIncludeSupported())
    {
        std::vector<const char*> includeCStrings;
        for (const auto& include : m_includes)
        {
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
    if (ARBIncludeSupported())
    {
        for (const auto& include : m_includes)
        {
            glDeleteNamedStringARB(util::glLength(include.first),
                                   include.first.c_str());
        }
    }
}

Shader::Shader(Shader&& old) : m_name{old.m_name}, m_shader{old.m_shader}
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
    return static_cast<GLboolean>(isCompiled) != GL_FALSE;
}

void Shader::printCompilationError() const
{
    std::cout << "Compilation failed for " << m_name << ":" << std::endl;
    GLint length;
    glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &length);
    char* infoLog = new char[length + 1];
    glGetShaderInfoLog(m_shader, length, NULL, infoLog);
    std::cout << infoLog << std::endl;
    delete[] infoLog;
}
