#pragma once

#include "util.h"

class Renderer {
public:
    Renderer();
    virtual ~Renderer();

    virtual void init() = 0;
    virtual void render(const util::Viewport& viewport) = 0;
    virtual void reload() = 0;
};
