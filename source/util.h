#pragma once

#include <string>
#include <vector>

#include <glbinding/gl/gl.h>
#define glCheckErrors() glCheckErrorsIn(__LINE__, __FILE__)

namespace util
{
    using namespace gl;

    struct Viewport {
        GLint x, y, width, height;
    };

    Viewport viewport();

    void setViewport(Viewport);

    template<typename T>
    GLint glLength(T object) {
        return static_cast<GLint>(object.size());
    }

    void glContextInfo();
    void glCheckErrorsIn(unsigned int line, std::string file);

    bool glExtensionSupported(std::string extension);
    std::string glslVersion();

    std::string loadFile(std::string filename);
    std::string toString(const GLubyte * glString);
    // replaces first occurence of old in target
    void replace(std::string& target, const std::string& old, const std::string& with);
    // splits string at first occurence
    std::pair<std::string, std::string> split(const std::string& string, const std::string& at);
    bool contains(const std::string& string, const std::string& substring);

    // A container that can be constructed with rvalue-references to its elements.
    // All objects will be moved instead of copied like when using initializer lists.
    template<typename T>
    class Group
    {
    public:
        Group(T&& element)
        {
            v.push_back(std::move(element));
        }

        template<typename ... T2>
        Group(T&& element, T2&&... rest)
            : Group(std::forward<T2>(rest)...)
        {
            v.push_back(std::move(element));
        }

        ~Group() {}

        typename std::vector<T>::const_reverse_iterator begin() const
        {
            return v.crbegin();
        }
        typename std::vector<T>::const_reverse_iterator end() const
        {
            return v.crend();
        }

    private:
        std::vector<T> v;
    };

}
