#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <utilgpu/cpp/file.h>
#include <utilgpu/cpp/resource.h>
#include <utilgpu/cpp/str.h>
#include <utilgpu/gl/Framebuffer.h>
#include <utilgpu/gl/base.h>
#include <utilgpu/qt/Config.h>
#include <utilgpu/window/Window.h>

#include "ProceduralRenderer.h"
#include "Project.h"

int main(int argc, char* argv[])
{
    util::Config config{"simonkrogmann", "procedural-viewer"};
    config.setDefaults({
        {"gl-version", "best"},
        {"file-resolution", "3840x2160"},
        {"fullscreen", "false"},
    });
    config.load(argc, argv);

    const auto arguments = config.additionalArguments();
    const auto openFile =
        (arguments.size() > 1)
            ? util::File{arguments[1]}
            : util::loadResource<procedural>("shader/default.frag");
    if (!openFile.exists())
    {
        std::cout << openFile.path << " does not exist." << std::endl;
        exit(1);
    }
    Project project{openFile};
    if (!project.valid())
    {
        std::cout << "Invalid project file." << std::endl;
        exit(2);
    }

    util::Window w;
    const auto resolution = config.value("file-resolution");
    const auto numbers = util::splitNumbers(resolution, "x");
    w.setFileResolution(numbers.first, numbers.second);

    const auto version = config.value("gl-version");
    if (version != "best")
    {
        const auto numbers = util::splitNumbers(version, ".");
        w.requestGLVersion(numbers.first, numbers.second);
    }
    w.init("procedural-viewer", config.value<bool>("fullscreen"));
    util::glInitialize();
    util::glContextInfo();
    w.initAfterGL();

    auto renderer = std::make_unique<ProceduralRenderer>(
        project.includes(), project.textures(), project.stages());

    w.setRenderer(std::move(renderer));
    w.loop();

    return 0;
}
