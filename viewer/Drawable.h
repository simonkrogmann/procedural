#pragma once

#include <glbinding/gl/gl.h>

using namespace gl;

class Drawable
{
public:
    Drawable();
    virtual ~Drawable();

    virtual void draw();

protected:
    GLuint m_vao;
};
