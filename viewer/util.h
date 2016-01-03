#pragma once

#include <string>
#include <vector>
#include <memory>

#include <glbinding/gl/gl.h>
#include <QImage>

namespace util
{
using namespace gl;

class StateKeeper
{
public:
    StateKeeper(const std::function<void()>& restoreFunction)
        : m_restoreFunction{restoreFunction}
    {
    }
    StateKeeper(const StateKeeper&) = delete;
    StateKeeper(const StateKeeper&&) {}
    ~StateKeeper() { m_restoreFunction(); }
private:
    std::function<void()> m_restoreFunction;
};

std::string loadFile(const std::string& filename);
struct File
{
    std::string name;
    std::string path;
    std::string content() const { return loadFile(path); }
};

namespace viewport
{
struct Viewport
{
    int x, y;
    unsigned int width, height;
};

Viewport get();

void set(const Viewport& data);

StateKeeper use(const Viewport& resolution);
}

GLint glGetInteger(const GLenum& symbol);

template <typename T>
GLint glLength(const T& object)
{
    return static_cast<GLint>(object.size());
}

void glContextInfo();

bool glExtensionSupported(const std::string& extension);
std::string glslVersion();

QImage loadImage(const std::string& filename);
void saveImage(const std::vector<unsigned char>& data, const int& width,
               const int& height, const std::string& filename);

std::string toString(const GLubyte* glString);
// replaces first occurence of old in target
void replace(std::string& target, const std::string& old,
             const std::string& with);
// splits string at first occurence
std::pair<std::string, std::string> split(const std::string& string,
                                          const std::string& at);
std::pair<std::string, std::string> rsplit(const std::string& string,
                                           const std::string& at);
bool contains(const std::string& string, const std::string& substring);
bool endsWith(const std::string& string, const std::string& ending);
std::pair<int, int> splitNumbers(const std::string& string,
                                 const std::string& at);

// A container that can be constructed with rvalue-references to its elements.
// All objects will be moved instead of copied like when using initializer
// lists.
template <typename T>
class Group
{
public:
    Group(T&& element) { v.push_back(std::move(element)); }
    template <typename... T2>
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

class YAMLNode
{
public:
    static std::unique_ptr<YAMLNode> parseYAML(std::string filename);

    YAMLNode(YAMLNode* parent = nullptr, int level = -1)
        : m_parent{parent}, m_level{level}
    {
    }

    YAMLNode* parent() const { return m_parent; }
    const std::map<std::string, std::unique_ptr<YAMLNode>>& children() const
    {
        return m_children;
    }
    YAMLNode* operator[](const std::string& key);
    const std::vector<std::string>& values() const { return m_values; }
    std::string value() const { return m_values[0]; }
    bool isLeaf() const { return m_children.size() > 0; }
private:
    YAMLNode* m_parent;
    std::map<std::string, std::unique_ptr<YAMLNode>> m_children;
    std::vector<std::string> m_values;
    int m_level;
};

// implements only a subset of yaml
std::unique_ptr<YAMLNode> parseYAML(std::string filename);
}
