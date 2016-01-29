#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <utilgpu/cpp/str.h>
#include <utilgpu/cpp/file.h>
#include <utilgpu/cpp/resource.h>
#include <utilgpu/qt/Config.h>
#include <utilgpu/gl/base.h>
#include <utilgpu/gl/Shader.h>

#include "Window.h"
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

    // increase id to work around program crashes,
    // where the shader id couldn't be synced properly
    Shader::id = config.valueUInt("shader-id") + 100;
    config.setValue("shader-id", Shader::id);
    const auto arguments = config.additionalArguments();
    const auto openFile = (arguments.size() > 1)
                              ? util::File{arguments[1]}
                              : loadResource<procedural>("shader/default.frag");
    Project project{openFile};
    if (!project.valid())
    {
        std::cout << "Invalid project file" << std::endl;
        exit(1);
    }

    Window w;
    const auto resolution = config.value("file-resolution");
    const auto numbers = util::splitNumbers(resolution, "x");
    w.setFileResolution(numbers.first, numbers.second);

    const auto version = config.value("gl-version");
    if (version != "best")
    {
        const auto numbers = util::splitNumbers(version, ".");
        w.requestGLVersion(numbers.first, numbers.second);
    }
    w.init("procedural-viewer", config.value("fullscreen") == "true");
    util::glInitialize();
    util::glContextInfo();
    w.initAfterGL();

    auto renderer = std::make_unique<ProceduralRenderer>(
        project.includes(), project.textures(), project.stages());

    w.setRenderer(std::move(renderer));
    w.loop();

    config.setValue("shader-id", Shader::id);
    return 0;
}
