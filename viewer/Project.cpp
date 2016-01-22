#include "Project.h"

#include <iostream>

#include <utilgpu/cpp/file.h>
#include <utilgpu/cpp/str.h>
#include <utilgpu/cpp/cfl.h>

Project::Project(const std::string& filename)
{
    if (util::endsWith(filename, ".frag"))
    {
        m_stages.push_back({"final", filename});
    }
    else
    {
        const auto folder = util::rsplit("./" + filename, "/").first + "/";
        const auto document = util::parseCFL(filename);
        if (!document->valid())
        {
            std::cout << document->message() << std::endl;
            m_valid = false;
            return;
        }
        auto& root = *document;
        const std::string includeLocation = "../library/";
        for (const auto& include : root["internal-includes"]->values())
        {
            m_internal.push_back(
                {include, includeLocation + include + ".frag"});
        }
        for (const auto& include : root["external-includes"]->children())
        {
            m_external.push_back({include->name(), folder + include->value()});
        }
        for (const auto& texture : root["textures"]->children())
        {
            m_textures.push_back({texture->name(), folder + texture->value()});
        }
        for (const auto& stage : root["stages"]->children())
        {
            m_stages.push_back({stage->name(), folder + stage->value()});
        }
    }

    // check for file existence
    checkExists(m_internal);
    checkExists(m_external);
    checkExists(m_textures);
    checkExists(m_stages);
}

Project::~Project()
{
}

void Project::checkExists(const std::vector<util::File>& files)
{
    for (const auto& file : files)
    {
        if (!file.exists())
        {
            std::cout << file.path << " does not exist." << std::endl;
            m_valid = false;
        }
    }
}

std::vector<util::File> Project::includes() const
{
    std::vector<util::File> includeFiles;

    for (const auto& include : m_internal)
    {
        includeFiles.push_back(include);
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

bool Project::valid() const
{
    return m_valid;
}
