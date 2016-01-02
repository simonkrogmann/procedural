#include "util.h"

#include <fstream>

namespace
{
    int leadingSpaces(const std::string& string)
    {
        int number = 0;
        for (; string[number] == ' '; ++number);
        return number;
    }
}

namespace util
{
    std::unique_ptr<YAMLNode> parseYAML(std::string filename)
    {
        return YAMLNode::parseYAML(filename);
    }

    std::unique_ptr<YAMLNode> YAMLNode::parseYAML(std::string filename)
    {
        auto root = std::make_unique<YAMLNode>();
        auto current = root.get();

        std::ifstream sourceFile(filename);
        std::string line;
        while (std::getline(sourceFile, line)) {
            auto level = leadingSpaces(line);
            if (line[level] == '#') continue;
            for (; current->m_level >= level; current = current->parent());
            if (line[level] == '-')
            {
                ++level;
                for (; line[level] == ' '; ++level);
                current->m_values.push_back(line.substr(level));
            }
            else
            {
                const auto pos = line.find(":");
                const auto key = line.substr(level, pos - level);
                current->m_children[key] = std::make_unique<YAMLNode>(current, level);
                current = (*current)[key];

                const auto rest = line.substr(pos + 1);
                const auto spaces = leadingSpaces(rest);
                const auto value = rest.substr(spaces);
                if (value.size() > 0)
                {
                    current->m_values.push_back(value);
                }
            }
        }
        return root;
    }

    YAMLNode* YAMLNode::operator[](const std::string& key)
    {
        if (m_children.find(key) == m_children.end()) {
            m_children[key] = std::make_unique<YAMLNode>(this, m_level + 1);
        }
        return m_children[key].get();
    }
}
