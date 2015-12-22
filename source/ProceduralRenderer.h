#pragma once

#include "Renderer.h"
#include "ScreenAlignedQuad.h"
#include "ShaderProgram.h"

class ProceduralRenderer : public Renderer {
public:
    ProceduralRenderer();
    virtual ~ProceduralRenderer();

    virtual void init() override;
    virtual void render() override;

private:
    ScreenAlignedQuad screen;
    ShaderProgram shader;
};
