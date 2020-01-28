#version 330
#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) out vec4 fragColor;
in vec2 normalizedCoord;
vec2 fragCoord = gl_FragCoord.xy;

uniform vec2 iResolution;
uniform float iTime;
uniform int iFrame;

// The symbols below will be auto-replaced
//textures
//includes
//main
