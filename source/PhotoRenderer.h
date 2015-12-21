#pragma once

#include "Renderer.h"
#include "ScreenAlignedQuad.h"
#include "ShaderProgram.h"

class PhotoRenderer : public Renderer {
public:
    PhotoRenderer();
    virtual ~PhotoRenderer();

    virtual void init() override;
    virtual void render() override;

private:
    ScreenAlignedQuad screen;
    ShaderProgram shader;
};
