#version 330
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0)in vec2 vertex;

out vec2 normalizedCoord;

void main() {
    gl_Position = vec4(vertex, 0.0, 1.0);
    normalizedCoord = vertex / 2.0 + 0.5;
}
