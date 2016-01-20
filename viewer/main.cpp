#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <glbinding/Binding.h>
#include <glbinding/gl/gl.h>
#include <glbinding/callbacks.h>
#include <QSettings>
#include <utilgpu/gl/base.h>
#include <utilgpu/cpp/str.h>
#include <utilgpu/qt/Config.h>

#include "Window.h"
#include "ProceduralRenderer.h"
#include "Shader.h"
#include "Project.h"

using namespace gl;

void initializeGL()
{
    glbinding::Binding::initialize(false);
    glbinding::setCallbackMaskExcept(
        glbinding::CallbackMask::After | glbinding::CallbackMask::Parameters,
        {"glGetError"});
    glbinding::setAfterCallback(
        [](const glbinding::FunctionCall& call)
        {
            const auto error = glGetError();
            if (error != GL_NO_ERROR)
            {
                std::cout << error << " in " << call.function->name()
                          << " with parameters:" << std::endl;
                for (const auto& parameter : call.parameters)
                {
                    std::cout << "    " << parameter->asString() << std::endl;
                }
            }
        });
}

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
    const auto openFile =
        (arguments.size() > 1) ? arguments[1] : "../viewer/shader/default.frag";
    Project project{openFile};

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
    initializeGL();
    util::glContextInfo();
    w.initAfterGL();

    auto renderer = std::make_unique<ProceduralRenderer>(
        project.includes(), project.textures(), project.stages());

    w.setRenderer(std::move(renderer));
    w.loop();

    config.setValue("shader-id", Shader::id);
    return 0;
}
