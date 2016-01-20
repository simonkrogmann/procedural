#pragma once

#include <vector>
#include <string>

#include <utilgpu/cpp/file.h>

class Project
{
public:
    Project(const std::string& filename);
    ~Project();

    std::vector<util::File> includes() const;
    std::vector<util::File> textures() const;
    std::vector<util::File> stages() const;

private:
    std::vector<std::string> m_internal;
    std::vector<util::File> m_external;
    std::vector<util::File> m_stages;
    std::vector<util::File> m_textures;
};
