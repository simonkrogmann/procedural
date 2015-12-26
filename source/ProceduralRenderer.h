#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "Renderer.h"
#include "ScreenAlignedQuad.h"
#include "Program.h"
#include "Texture.h"

class ProceduralRenderer : public Renderer {
public:
    ProceduralRenderer(const std::vector<std::string>& includes,
        const std::map<std::string, std::string>& textureFiles);
    virtual ~ProceduralRenderer();

    virtual void init() override;
    virtual void render() override;
    virtual void reload() override;

private:
    ScreenAlignedQuad m_screen;
    std::unique_ptr<Program> m_program;
    std::vector<std::string> m_includes;
    std::vector<Texture> m_textures;
};
