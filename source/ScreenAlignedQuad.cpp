#include "ScreenAlignedQuad.h"

#include <glbinding/gl/gl.h>

using namespace gl;

ScreenAlignedQuad::ScreenAlignedQuad() {
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    GLuint buffer;

    const float data[] = {
        -1.0, 1.0,
        1.0, 1.0,
        -1.0, -1.0,
        1.0, -1.0
    };

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 4, &data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glDeleteBuffers(1, &buffer);
}

ScreenAlignedQuad::~ScreenAlignedQuad() {
    glDeleteVertexArrays(1, &m_vao);
}


void ScreenAlignedQuad::draw() {
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

