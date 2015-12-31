#version 140
#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) out vec4 color;
in vec2 position;

uniform ivec2 windowSize;

// The symbols below will be auto-replaced
#id
#textures
#includes

void main()
{
    vec4 sphereData = sphere(position, vec2(0.5, 0.5), 0.2, vec2(windowSize));
    vec3 light = normalize(vec3(1, 1, 1));
    vec3 sphereColor = vec3(0.3, 0.3, 0.9);
    vec3 eye = vec3(0, 0, 1);
    vec4 factors = vec4(0, 0.6, 0, 16);
    color = vec4(sphereData.a * phong(sphereData.xyz, light, eye, factors) * sphereColor, 0);
}
