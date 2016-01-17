#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <chrono>

#include <utilgpu/cpp/file.h>

#include "Renderer.h"
#include "ScreenAlignedQuad.h"
#include "Program.h"
#include "Texture.h"

class ProceduralRenderer : public Renderer
{
public:
    ProceduralRenderer(const std::vector<util::File>& includes,
                       const std::vector<util::File>& textureFiles);
    virtual ~ProceduralRenderer();

    virtual void init() override;
    virtual void reload() override;

protected:
    virtual void draw(const util::viewport::Viewport& viewport) override;

private:
    void reloadProgram();
    void reloadTextures();

    const static std::string shaderLocation;

    ScreenAlignedQuad m_screen;
    std::unique_ptr<Program> m_program;
    std::vector<util::File> m_includes;
    std::vector<Texture> m_textures;
    std::chrono::time_point<std::chrono::steady_clock> m_start;
};
