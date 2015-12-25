#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#include "Window.h"
#include "ProceduralRenderer.h"
#include "util.h"


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
        if (argument.substr(0, 2) == "--" && util::contains(argument, "="))
        {
            auto split = util::split(argument.substr(2), "=");
            options[split.first] = split.second;
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
        if (util::contains(version, "."))
        {
            auto numbers = util::split(version, ".");
            int major, minor;
            std::istringstream(numbers.first) >> major;
            std::istringstream(numbers.second) >> minor;
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
