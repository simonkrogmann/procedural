#pragma once

#include "Drawable.h"

class ScreenAlignedQuad : public Drawable {
public:
    ScreenAlignedQuad();
    virtual ~ScreenAlignedQuad();

    virtual void draw() override;
};
