#include "ProceduralRenderer.h"

#include <glbinding/gl/gl.h>

#include "Shader.h"
#include "util.h"

using namespace gl;

ProceduralRenderer::ProceduralRenderer(const std::vector<std::string>& includes,
    const std::map<std::string, std::string>& textureFiles)
: Renderer { }
, m_screen { }
, m_program { }
, m_includes { includes }
, m_textures { }
{
    for (const auto& textureFile : textureFiles)
    {
        m_textures.push_back(Texture(textureFile.first, textureFile.second));
    }
}

ProceduralRenderer::~ProceduralRenderer()
{

}

void ProceduralRenderer::init()
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
    reload();
}

void ProceduralRenderer::reload()
{
    const std::string shaderLocation = "../source/shader/";
    auto fragmentCode = util::loadFile(shaderLocation + "procedural.frag");
    std::string textureString = "", includeString = "";
    for (const auto& texture : m_textures)
    {
        textureString += Shader::textureString(texture.name());
    }
    for (const auto& include : m_includes)
    {
        textureString += Shader::includeString(include);
    }
    util::replace(fragmentCode, "#textures", textureString);
    util::replace(fragmentCode, "#includes", includeString);
    util::Group<Shader> shaders (
        Shader::vertex(shaderLocation + "screenalignedquad.vert"),
        Shader("procedural.frag", fragmentCode, GL_FRAGMENT_SHADER, m_includes)
    );
    m_program = std::make_unique<Program>(shaders);

    m_program->use();
    unsigned int i = 0;
    for (auto& texture : m_textures)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        texture.load();
        auto location = m_program->getUniformLocation(texture.name());
        glUniform1i(location, i);
        ++i;
    }
}


void ProceduralRenderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->use();
    auto loc = m_program->getUniformLocation("windowSize");
    auto size = util::windowSize();
    glUniform2i(loc, size.x, size.y);
    m_screen.draw();
}
