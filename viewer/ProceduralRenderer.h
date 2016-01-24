#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <chrono>

#include <utilgpu/cpp/file.h>
#include <utilgpu/gl/ScreenAlignedQuad.h>
#include <utilgpu/gl/Program.h>
#include <utilgpu/gl/Texture.h>

#include "Renderer.h"

struct Stage
{
    Stage(const std::string& name) : name{name}, program{}, framebuffer{} {}
    std::string name;
    std::unique_ptr<Program> program;
    std::unique_ptr<Framebuffer> framebuffer;
};

class ProceduralRenderer : public Renderer
{
public:
    ProceduralRenderer(const std::vector<util::File>& includes,
                       const std::vector<util::File>& textureFiles,
                       const std::vector<util::File>& stages);
    virtual ~ProceduralRenderer();

    virtual void init() override;
    virtual void reload() override;
    virtual void saveFramebuffers() override;

protected:
    virtual void draw(const util::viewport::Viewport& viewport) override;

private:
    void reloadStages();
    void reloadTextures();

    const static std::string shaderLocation;

    ScreenAlignedQuad m_screen;
    std::vector<util::File> m_includes;
    std::vector<Texture> m_textures;
    std::vector<util::File> m_stageShaders;
    std::vector<Stage> m_stages;
    std::chrono::time_point<std::chrono::steady_clock> m_start;
};
