#pragma once

#include "Renderer.h"
#include "ScreenAlignedQuad.h"
#include "Program.h"

class ProceduralRenderer : public Renderer {
public:
    ProceduralRenderer();
    virtual ~ProceduralRenderer();

    virtual void init() override;
    virtual void render() override;

private:
    ScreenAlignedQuad m_screen;
    Program m_program;
};
