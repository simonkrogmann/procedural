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
#include "util.h"


using namespace gl;

int main(int argc, char * argv[]) {
    Config config {argc, argv};
    auto additionalArguments = config.additionalArguments();

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
        auto error = glGetError();
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

    std::vector<std::string> includes {"util", "lighting", "sphere", "gradient", "chess"};
    std::map<std::string, std::string> textures { };
    auto renderer = std::make_unique<ProceduralRenderer>(includes, textures);

    w.setRenderer(std::move(renderer));
    w.loop();

    return 0;
}
