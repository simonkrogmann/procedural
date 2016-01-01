#pragma once

#include <string>
#include <vector>

#include <glbinding/gl/gl.h>
#include <QImage>

#define glCheckErrors() glCheckErrorsIn(__LINE__, __FILE__)

namespace util
{
    using namespace gl;

    class StateKeeper {
    public:
        StateKeeper(const std::function<void()>& restoreFunction)
            : m_restoreFunction {restoreFunction} {}
        StateKeeper(const StateKeeper&) = delete;
        StateKeeper(const StateKeeper&&) {}
        ~StateKeeper() { m_restoreFunction(); }
    private:
        std::function<void()> m_restoreFunction;
    };

    namespace viewport
    {
        struct Viewport {
            int x, y;
            unsigned int width, height;
        };

        Viewport get();

        void set(const Viewport& data);

        StateKeeper use(const Viewport& resolution);
    }

    GLint glGetInteger(const GLenum& symbol);

    template<typename T>
    GLint glLength(const T& object) {
        return static_cast<GLint>(object.size());
    }

    void glContextInfo();
    void glCheckErrorsIn(const unsigned int& line, const std::string& file);

    bool glExtensionSupported(const std::string& extension);
    std::string glslVersion();

    QImage loadImage(const std::string& filename);
    void saveImage(const std::vector<unsigned char>& data,
        const int& width, const int& height, const std::string& filename);

    std::string loadFile(const std::string& filename);
    std::string toString(const GLubyte * glString);
    // replaces first occurence of old in target
    void replace(std::string& target, const std::string& old, const std::string& with);
    // splits string at first occurence
    std::pair<std::string, std::string> split(const std::string& string, const std::string& at);
    bool contains(const std::string& string, const std::string& substring);
    std::pair<int, int> splitNumbers(const std::string& string, const std::string& at);

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
