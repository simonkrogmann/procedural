#pragma once

#include <string>
#include <vector>
#include <map>

#include <glbinding/gl/gl.h>

using namespace gl;

class Shader
{
public:
    static bool ARBIncludeSupported();
    static Shader vertex(const std::string& filename,
        const std::vector<std::string>& includes = {});
    static Shader geometry(const std::string& filename,
        const std::vector<std::string>& includes = {});
    static Shader fragment(const std::string& filename,
        const std::vector<std::string>& includes = {});
    static Shader compute(const std::string& filename,
        const std::vector<std::string>& includes = {});
    Shader(Shader&& old);
    Shader(const Shader&) = delete;
    Shader(const std::string& name, const std::string& source,
        const GLenum& type, const std::vector<std::string>& includes = {});
    ~Shader();

    bool isCompiled() const;
    void printCompilationError() const;
    GLuint get() const { return m_shader; }
private:
    void includeShader(const std::string& name, const std::string& source);
    void compileShader(const std::string& source);
    void deleteIncludes();

    std::string m_name;
    GLuint m_shader;
    std::map<std::string, std::string> m_includes;
};
