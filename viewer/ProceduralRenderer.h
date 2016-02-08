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
#include <utilgpu/gl/Renderer.h>

namespace util
{
class Framebuffer;
}

struct Stage
{
    Stage(const std::string& name) : name{name}, program{}, framebuffer{} {}
    std::string name;
    std::unique_ptr<util::Program> program;
    std::unique_ptr<util::Framebuffer> framebuffer;
};

class ProceduralRenderer : public util::Renderer
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

    util::ScreenAlignedQuad m_screen;
    std::vector<util::File> m_includes;
    std::vector<util::File> m_stageShaders;
    std::vector<util::File> m_textureFiles;
    std::vector<util::Texture> m_textures;
    std::vector<Stage> m_stages;
    std::chrono::time_point<std::chrono::steady_clock> m_start;
};
