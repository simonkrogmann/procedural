// uses includes:
//  - util

vec4 sphereHelper(vec2 uv, vec2 position, float radius)
{
    float height = sqrt(pow(radius, 2.0) - pow(length(uv - position), 2));
    vec3 normal = normalize(vec3(uv - position, height));
    float outside = aastep(radius, length(uv - position));
    return vec4(normal, 1.0 - outside);
}

vec4 sphere(vec2 uv, vec2 position, float radius, vec2 windowSize)
{
    vec2 centerUV = scaleToCenterSquare(uv, windowSize);
    return sphereHelper(centerUV, position, radius);
}
