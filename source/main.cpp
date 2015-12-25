#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

#include "Window.h"
#include "ProceduralRenderer.h"

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

using namespace gl;

std::map<std::string, std::string> parseArguments(int argc, char * argv[])
{
    std::vector<std::string> arguments;
    for (int i = 0; i < argc; ++i)
    {
        arguments.push_back(argv[i]);
    }

    std::map<std::string, std::string> options;
    for (auto& argument : arguments)
    {
        const auto equalPosition = argument.find("=");
        if (argument.substr(0, 2) == "--" && equalPosition != std::string::npos)
        {
            const auto key = argument.substr(2, equalPosition - 2);
            const auto value = argument.substr(equalPosition + 1);
            options[key] = value;
        }
    }
    return options;
}

int main(int argc, char * argv[]) {
    const auto options = parseArguments(argc, argv);

    Window w;
    if (options.find("gl") != options.end())
    {
        const auto version = options.at("gl");
        const auto dotPosition = version.find(".");
        if (dotPosition != std::string::npos)
        {
            int major, minor;
            std::istringstream(version.substr(0, dotPosition)) >> major;
            std::istringstream(version.substr(dotPosition + 1)) >> minor;
            w.requestGLVersion(major, minor);
        }
    }
    w.init("procedural");

    glbinding::Binding::initialize();
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    w.initAfterGL();

    std::vector<std::string> includes {"gradient", "chess"};
    auto renderer = std::make_unique<ProceduralRenderer>(includes);

    w.setRenderer(std::move(renderer));
    w.loop();

    return 0;
}
