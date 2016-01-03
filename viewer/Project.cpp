#include "Project.h"

#include "util.h"

Project::Project(const std::string& filename)
{
    if (util::endsWith(filename, ".frag"))
    {
        m_mainShader = filename;
    }
    else
    {
        const auto folder = util::rsplit("./" + filename, "/").first + "/";
        const auto document = util::parseYAML(filename);
        auto& root = *document;
        m_internal = root["internal-includes"]->values();
        for (const auto& include : root["external-includes"]->children())
        {
            m_external.push_back(
                {include.first, folder + include.second->value()});
        }
        for (const auto& texture : root["textures"]->children())
        {
            m_textures.push_back(
                {texture.first, folder + texture.second->value()});
        }
        m_mainShader = folder + (root["main"]->value());
    }
}

Project::~Project()
{
}

std::vector<util::File> Project::includes()
{
    std::vector<util::File> includeFiles;

    const std::string includeLocation = "../library/";
    for (const auto& include : m_internal)
    {
        includeFiles.push_back({include, includeLocation + include + ".frag"});
    }
    for (const auto& include : m_external)
    {
        includeFiles.push_back(include);
    }
    includeFiles.push_back({"main", m_mainShader});
    return includeFiles;
}

std::vector<util::File> Project::textures()
{
    return m_textures;
}
