#include "ProceduralRenderer.h"

#include <glbinding/gl/gl.h>
#include <utilpp/file.h>
#include <utilpp/Group.h>
#include <utilpp/str.h>
#include <utilpp/gl/viewport.h>

#include "Shader.h"

using namespace gl;

const std::string ProceduralRenderer::shaderLocation = "../viewer/shader/";

ProceduralRenderer::ProceduralRenderer(
    const std::vector<util::File>& includes,
    const std::vector<util::File>& textureFiles)
    : Renderer{}
    , m_screen{}
    , m_program{}
    , m_includes{includes}
    , m_textures{}
    , m_start{std::chrono::steady_clock::now()}
{
    for (const auto& textureFile : textureFiles)
    {
        m_textures.push_back(Texture(textureFile));
        addDependentPath(textureFile.path);
    }
    for (const auto& include : m_includes)
    {
        addDependentPath(include.path);
    }
    addDependentPath(shaderLocation + "procedural.frag");
    addDependentPath(shaderLocation + "screenalignedquad.vert");
}

ProceduralRenderer::~ProceduralRenderer()
{
}

void ProceduralRenderer::init()
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
    reload();
}

void ProceduralRenderer::reloadProgram()
{
    std::string textureString = "", includeString = "";
    for (const auto& texture : m_textures)
    {
        textureString += Shader::textureString(texture.name());
    }
    for (const auto& include : m_includes)
    {
        textureString += Shader::includeString(include.name);
    }

    auto fragmentCode = util::loadFile(shaderLocation + "procedural.frag");
    util::replace(fragmentCode, "//textures", textureString);
    util::replace(fragmentCode, "//includes", includeString);
    const util::Group<Shader> shaders(
        Shader::vertex(util::File{"screenalignedquad.vert",
                                  shaderLocation + "screenalignedquad.vert"}),
        Shader("procedural.frag", fragmentCode, GL_FRAGMENT_SHADER,
               m_includes));
    m_program = std::make_unique<Program>(shaders);
}

void ProceduralRenderer::reloadTextures()
{
    m_program->use();
    unsigned int i = 0;
    for (auto& texture : m_textures)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        texture.load();
        const auto location = m_program->getUniformLocation(texture.name());
        glUniform1i(location, i);
        ++i;
    }
}

void ProceduralRenderer::reload()
{
    reloadProgram();
    if (!m_program->isLinked())
    {
        return;
    }
    reloadTextures();
}

void ProceduralRenderer::draw(const util::viewport::Viewport& viewport)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!m_program->isLinked())
    {
        return;
    }

    std::chrono::duration<double> diff =
        std::chrono::steady_clock::now() - m_start;

    m_program->use();
    glUniform2i((*m_program)["windowSize"], viewport.width, viewport.height);
    glUniform1f((*m_program)["time"], diff.count());

    m_screen.draw();
}
