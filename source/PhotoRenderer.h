#pragma once

#include "Renderer.h"

class PhotoRenderer : public Renderer {
public:
    PhotoRenderer();
    virtual ~PhotoRenderer();

    virtual void init() override;
    virtual void render() override;
};
