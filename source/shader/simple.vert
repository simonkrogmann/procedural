#version 450

layout(location = 0)in vec2 vertex;

out vec2 position;

void main() {

    gl_Position = vec4(vertex, 0.0, 1.0);
    position = vertex / 2 + 0.5;
}
