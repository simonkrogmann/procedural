#include "util.h"

#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <map>

#include <glbinding/gl/gl.h>

namespace util
{
    using namespace gl;

    Size windowSize()
    {
        GLint data[4];
        glGetIntegerv(GL_VIEWPORT, data);
        return {data[2], data[3]};
    }

    std::string loadFile(std::string filename)
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

    bool glExtensionSupported(std::string extension)
    {
        auto extensionsRaw = glGetString(GL_EXTENSIONS);
        glGetError();
        if (extensionsRaw == NULL)
        {
            return false;
        }
        std::string extensions = toString(glGetString(GL_EXTENSIONS));
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
        if (position != std::string::npos)
        {
            return {string.substr(0, position), string.substr(position + at.length())};
        }
        return {"", ""};
    }
    bool contains(const std::string& string, const std::string& substring)
    {
        return string.find(substring) != std::string::npos;

    }
}