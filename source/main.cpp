#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <glbinding/Binding.h>
#include <glbinding/gl/gl.h>
#include <glbinding/callbacks.h>
#include <QSettings>

#include "Window.h"
#include "ProceduralRenderer.h"
#include "Config.h"
#include "Shader.h"
#include "util.h"


using namespace gl;

int main(int argc, char * argv[]) {
    Config config {argc, argv};
    Shader::id = config.valueUInt("shader-id");
    const auto additionalArguments = config.additionalArguments();

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
    w.init("procedural");

    glbinding::Binding::initialize(false);
    glbinding::setCallbackMaskExcept(
        glbinding::CallbackMask::After | glbinding::CallbackMask::Parameters,
        { "glGetError" });
    glbinding::setAfterCallback([](const glbinding::FunctionCall& call)
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

    util::glContextInfo();
    w.initAfterGL();

    const std::string includeLocation = "../source/shader/";
    const std::vector<util::File> includes {
        { "util", includeLocation + "util.glsl" },
        { "lighting", includeLocation + "lighting.glsl" },
        { "sphere", includeLocation + "sphere.glsl" },
        { "gradient", includeLocation + "gradient.glsl" },
        { "chess", includeLocation + "chess.glsl" },
    };
    const std::vector<util::File> textures { };
    auto renderer = std::make_unique<ProceduralRenderer>(includes, textures);

    w.setRenderer(std::move(renderer));
    w.loop();

    config.setValue("shader-id", Shader::id);
    return 0;
}
