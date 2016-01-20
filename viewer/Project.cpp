#include "Project.h"

#include <utilgpu/cpp/file.h>
#include <utilgpu/cpp/str.h>
#include <utilgpu/cpp/yaml.h>

Project::Project(const std::string& filename)
{
    if (util::endsWith(filename, ".frag"))
    {
        m_stages.push_back({"final", filename});
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
        for (const auto& stage : root["stages"]->children())
        {
            m_stages.push_back({stage.first, folder + stage.second->value()});
        }
    }
}

Project::~Project()
{
}

std::vector<util::File> Project::includes() const
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
    return includeFiles;
}

std::vector<util::File> Project::stages() const
{
    return m_stages;
}

std::vector<util::File> Project::textures() const
{
    return m_textures;
}
