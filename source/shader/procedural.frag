#version 450
#extension GL_ARB_shading_language_include : require

out vec4 color;
in vec2 position;

#include "/gradient"

void main() {
    color = vec4(gradient(position), 1.0);
}
