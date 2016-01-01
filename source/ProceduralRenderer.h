#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "Renderer.h"
#include "ScreenAlignedQuad.h"
#include "Program.h"
#include "Texture.h"
#include "util.h"

class ProceduralRenderer : public Renderer {
public:
    ProceduralRenderer(const std::vector<util::File>& includes,
        const std::vector<util::File>& textureFiles);
    virtual ~ProceduralRenderer();

    virtual void init() override;
    virtual void render(const util::viewport::Viewport& viewport) override;
    virtual void reload() override;
private:
    void reloadProgram();
    void reloadTextures();

    ScreenAlignedQuad m_screen;
    std::unique_ptr<Program> m_program;
    std::vector<util::File> m_includes;
    std::vector<Texture> m_textures;
};
