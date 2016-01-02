#pragma once

#include <string>
#include <vector>
#include <map>

#include <glbinding/gl/gl.h>

#include "util.h"

using namespace gl;

class Shader
{
public:
    static unsigned int id;
    static std::string uniqueId();

    static std::string includeString(const std::string& name);
    static std::string textureString(const std::string& name);
    static std::string idString();

    static Shader vertex(const std::string& filename,
        const std::vector<util::File>& includes = {});
    static Shader geometry(const std::string& filename,
        const std::vector<util::File>& includes = {});
    static Shader fragment(const std::string& filename,
        const std::vector<util::File>& includes = {});
    static Shader compute(const std::string& filename,
        const std::vector<util::File>& includes = {});

    Shader(Shader&& old);
    Shader(const Shader&) = delete;
    Shader(const std::string& name, const std::string& source,
        const GLenum& type, const std::vector<util::File>& includes = {});
    ~Shader();

    bool isCompiled() const;
    void printCompilationError() const;
    GLuint get() const { return m_shader; }
private:
    void includeShader(const std::string& name, const std::string& source);
    void compileShader(const std::string& source);
    void deleteIncludes();

    static bool ARBIncludeSupported();

    std::string m_name;
    GLuint m_shader;
    std::map<std::string, std::string> m_includes;
};
