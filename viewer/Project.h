#pragma once

#include <vector>
#include <string>

#include "util.h"

class Project
{
public:
    Project(const std::string& filename);
    ~Project();

    std::vector<util::File> includes();
    std::vector<util::File> textures();

private:
    std::vector<std::string> m_internal;
    std::vector<util::File> m_external;
    std::string m_mainShader;
    std::vector<util::File> m_textures;
};
