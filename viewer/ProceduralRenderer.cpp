#include "ProceduralRenderer.h"

#include <iostream>

#include <glbinding/gl/gl.h>
#include <utilgpu/cpp/file.h>
#include <utilgpu/cpp/resource.h>
#include <utilgpu/cpp/Group.h>
#include <utilgpu/cpp/str.h>
#include <utilgpu/gl/viewport.h>
#include <utilgpu/gl/Shader.h>

using namespace gl;

ProceduralRenderer::ProceduralRenderer(
    const std::vector<util::File>& includes,
    const std::vector<util::File>& textureFiles,
    const std::vector<util::File>& stages)
    : Renderer{}
    , m_screen{}
    , m_includes{includes}
    , m_textures{}
    , m_stageShaders{stages}
    , m_stages{}
    , m_start{std::chrono::steady_clock::now()}
{
    for (const auto& textureFile : textureFiles)
    {
        m_textures.push_back(util::Texture(textureFile));
        addDependentPath(textureFile);
    }
    for (const auto& include : m_includes)
    {
        addDependentPath(include);
    }
    for (const auto& stage : m_stageShaders)
    {
        addDependentPath(stage);
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

void ProceduralRenderer::reloadStages()
{
    std::string textureString = "", includeString = "";
    for (const auto& texture : m_textures)
    {
        textureString += util::Shader::textureString(texture.name());
    }
    for (const auto& include : m_includes)
    {
        includeString += util::Shader::includeString(include.name);
    }
    for (size_t i = 0; i < m_stageShaders.size(); ++i)
    {
        textureString += util::Shader::textureString(m_stageShaders[i].name);
    }

    auto fragmentFile = loadResource<procedural>("shader/procedural.frag");
    auto fragmentCode = fragmentFile.content();
    util::replace(fragmentCode, "//textures", textureString);
    util::replace(fragmentCode, "//includes", includeString);

    m_stages.clear();
    for (size_t i = 0; i < m_stageShaders.size(); ++i)
    {
        const auto& shader = m_stageShaders[i];
        auto stageCode = fragmentCode;
        util::replace(stageCode, "//main",
                      util::Shader::includeString(shader.name));
        auto includes = m_includes;
        includes.push_back(shader);
        const util::Group<util::Shader> shaders(
            util::Shader::vertex(
                loadResource<procedural>("shader/screenalignedquad.vert")),
            util::Shader("procedural.frag", stageCode, GL_FRAGMENT_SHADER,
                         includes));
        auto program = std::make_unique<util::Program>(shaders);
        auto fbo = (i != m_stageShaders.size() - 1)
                       ? new util::Framebuffer(10, 10)
                       : util::Framebuffer::None();
        m_stages.push_back({m_stageShaders[i].name});
        m_stages.back().program = std::move(program);
        m_stages.back().framebuffer = std::unique_ptr<util::Framebuffer>(fbo);
    }
}

void ProceduralRenderer::reloadTextures()
{
    for (const auto& stage : m_stages)
    {
        if (!stage.program->isLinked())
        {
            return;
        }
        stage.program->use();
        unsigned int textureIndex = 0;
        for (auto& texture : m_textures)
        {
            glActiveTexture(GL_TEXTURE0 + textureIndex);
            texture.load();
            const auto location =
                stage.program->getUniformLocation(texture.name());
            glUniform1i(location, textureIndex);
            ++textureIndex;
        }
        // add previous stages as textures
        for (const auto& textureStage : m_stages)
        {
            glActiveTexture(GL_TEXTURE0 + textureIndex);
            glBindTexture(GL_TEXTURE_2D, textureStage.framebuffer->getColor());
            const auto location =
                stage.program->getUniformLocation(textureStage.name);
            glUniform1i(location, textureIndex);
            ++textureIndex;
        }
    }
    std::cout << "Shaders successfully compiled" << std::endl;
}

void ProceduralRenderer::reload()
{
    reloadStages();
    reloadTextures();
}

void ProceduralRenderer::saveFramebuffers()
{
    for (const auto& stage : m_stages)
    {
        if (stage.framebuffer->get() != 0)
            stage.framebuffer->save(stage.name + ".png");
    }
}

void ProceduralRenderer::draw(const util::viewport::Viewport& viewport)
{
    for (const auto& stage : m_stages)
    {
        stage.framebuffer->resize(viewport);
        auto keeper = stage.framebuffer->use();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (!stage.program->isLinked())
        {
            return;
        }

        std::chrono::duration<double> diff =
            std::chrono::steady_clock::now() - m_start;

        stage.program->use();
        glUniform2i((*stage.program)["windowSize"], viewport.width,
                    viewport.height);
        glUniform1f((*stage.program)["time"], diff.count());

        m_screen.draw();
    }
}
