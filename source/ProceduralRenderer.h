#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Renderer.h"
#include "ScreenAlignedQuad.h"
#include "Program.h"

class ProceduralRenderer : public Renderer {
public:
    ProceduralRenderer(const std::vector<std::string>& includes);
    virtual ~ProceduralRenderer();

    virtual void init() override;
    virtual void render() override;
    virtual void recompile() override;

private:
    ScreenAlignedQuad m_screen;
    std::unique_ptr<Program> m_program;
    std::vector<std::string> m_includes;
};
