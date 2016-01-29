#pragma once

#include <vector>
#include <string>

#include <utilgpu/cpp/file.h>

class Project
{
public:
    Project(const util::File& file);
    ~Project();

    std::vector<util::File> includes() const;
    std::vector<util::File> textures() const;
    std::vector<util::File> stages() const;
    bool valid() const;

private:
    void checkExists(const std::vector<util::File>& files);

    std::vector<util::File> m_internal;
    std::vector<util::File> m_external;
    std::vector<util::File> m_stages;
    std::vector<util::File> m_textures;
    bool m_valid = true;
};
