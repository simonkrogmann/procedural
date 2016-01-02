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

std::vector<util::File> collectIncludes(const std::vector<std::string>& internal,
    const std::vector<util::File>& external, const std::string& mainShader)
{
    std::vector<util::File> includes;

    const std::string includeLocation = "../library/";
    for (const auto& include : internal)
    {
        includes.push_back({include, includeLocation + include + ".glsl"});
    }
    for (const auto& include : external)
    {
        includes.push_back(include);
    }
    includes.push_back({"main", mainShader});
    return includes;
}

void initializeGL()
{
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
}

int main(int argc, char * argv[]) {
    Config config {argc, argv};
    Shader::id = config.valueUInt("shader-id");
    const auto arguments = config.additionalArguments();

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
    initializeGL();
    util::glContextInfo();
    w.initAfterGL();

    const auto openFile = (arguments.size() > 1) ? arguments[1] : "../viewer/shader/default.glsl";
    std::vector<std::string> internal;
    std::vector<util::File> external;
    std::string mainShader;
    std::vector<util::File> textures;
    if (util::endsWith(openFile, ".glsl"))
    {
        mainShader = openFile;
    }
    else
    {
        internal = {"util", "lighting", "sphere"};
        external = {{"settings", "../examples/sphere/settings.glsl"}};
        mainShader = "../examples/sphere/main.glsl";
    }
    const auto includes = collectIncludes(internal, external, mainShader);
    auto renderer = std::make_unique<ProceduralRenderer>(includes, textures);

    w.setRenderer(std::move(renderer));
    w.loop();

    config.setValue("shader-id", Shader::id);
    return 0;
}
