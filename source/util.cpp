#include "util.h"

#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <map>
#include <cassert>
#include <iostream>

#include <glbinding/gl/gl.h>

namespace util
{
    using namespace gl;

    namespace viewport
    {
        Viewport get()
        {
            GLint data[4];
            glGetIntegerv(GL_VIEWPORT, data);
            assert(data[2] >= 0 && data[3] >= 0);

            return {data[0], data[1], static_cast<unsigned int>(data[2]), static_cast<unsigned int>(data[3])};
        }

        void set(const Viewport& data)
        {
            glViewport(data.x, data.y, data.width, data.height);
        }

        StateKeeper use(const Viewport& resolution) {
            const auto old = get();
            set(resolution);
            return { [=]() { set(old); } };
        }
    }

    void glContextInfo()
    {
        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    }

    GLint glGetInteger(const GLenum& symbol)
    {
        GLint value;
        glGetIntegerv(symbol, &value);
        return value;
    }

    std::string loadFile(const std::string& filename)
    {
        std::ifstream sourceFile(filename);

        std::stringstream sourceBuffer;
        sourceBuffer << sourceFile.rdbuf();
        return sourceBuffer.str();
    }

    std::string toString(const GLubyte * glString)
    {
        return reinterpret_cast<char const *>(glString);
    }

    bool glExtensionSupported(const std::string& extension)
    {
        const auto extensionsRaw = glGetString(GL_EXTENSIONS);
        if (extensionsRaw == NULL)
        {
            glGetError();
            return false;
        }
        const std::string extensions = toString(glGetString(GL_EXTENSIONS));
        return extensions.find(extension) != std::string::npos;
    }

    std::string glslVersion()
    {
        int major = 0;
        int minor = 0;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        const std::string glVersion = std::to_string(major) + std::to_string(minor);
        const std::map<std::string, std::string> glslVersionMapping {
            {"20", "110"},
            {"21", "120"},
            {"30", "130"},
            {"31", "140"},
            {"32", "150"},
        };
        if (glslVersionMapping.find(glVersion) != glslVersionMapping.end())
        {
            return glslVersionMapping.at(glVersion);
        }
        return glVersion + "0";
    }

    void replace(std::string& target, const std::string& old, const std::string& with)
    {
        const auto position = target.find(old);
        target.replace(position, old.length(), with);
    }

    std::pair<std::string, std::string> split(const std::string& string, const std::string& at)
    {
        const auto position = string.find(at);
        assert(position != std::string::npos);
        return {string.substr(0, position), string.substr(position + at.length())};
    }

    bool contains(const std::string& string, const std::string& substring)
    {
        return string.find(substring) != std::string::npos;
    }

    std::pair<int, int> splitNumbers(const std::string& string, const std::string& at)
    {
        const auto numbers = util::split(string, at);
        int first, second;
        std::istringstream(numbers.first) >> first;
        std::istringstream(numbers.second) >> second;
        return {first, second};
    }
}
