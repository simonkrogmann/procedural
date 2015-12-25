#version 140
#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) out vec4 color;
in vec2 position;

uniform ivec2 windowSize;

#include "/gradient"
#include "/chess"


void main() {
    color = vec4(chessSquare(position, vec2(windowSize), 8), 1.0);
}
