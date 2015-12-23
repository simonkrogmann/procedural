#version 450
#extension GL_ARB_shading_language_include : require

out vec4 color;
in vec2 position;

#include "/gradient"
#include "/chess"

void main() {
    color = vec4(chess(position, 8), 1.0);
}
