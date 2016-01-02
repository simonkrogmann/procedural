#include "ProceduralRenderer.h"

#include <glbinding/gl/gl.h>

#include "Shader.h"
#include "util.h"

using namespace gl;

const std::string ProceduralRenderer::shaderLocation = "../viewer/shader/";

ProceduralRenderer::ProceduralRenderer(const std::vector<util::File>& includes,
    const std::vector<util::File>& textureFiles)
: Renderer { }
, m_screen { }
, m_program { }
, m_includes { includes }
, m_textures { }
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
    util::replace(fragmentCode, "#textures", textureString);
    util::replace(fragmentCode, "#includes", includeString);
    const util::Group<Shader> shaders (
        Shader::vertex(shaderLocation + "screenalignedquad.vert"),
        Shader("procedural.frag", fragmentCode, GL_FRAGMENT_SHADER, m_includes)
    );
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

    m_program->use();
    const auto loc = m_program->getUniformLocation("windowSize");
    glUniform2i(loc, viewport.width, viewport.height);
    m_screen.draw();
}
