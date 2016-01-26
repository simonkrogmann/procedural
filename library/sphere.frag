// uses includes:
//  - util
//  - math

vec4 sphere(vec2 uv, vec2 position, float radius)
{
    float heightSquared = pow(radius, 2.0) - pow(length(uv - position), 2);
    float height = (heightSquared >= 0) ? sqrt(heightSquared) : 0.0;
    vec3 normal = normalize(vec3(uv - position, height));
    float outside = aastep(radius, length(uv - position));
    return vec4(normal, 1.0 - outside);
}

vec2 polar(vec3 normal)
{
    float x = atan(normal.x, normal.z) / (2.0 * pi);
    float y = 1.0 * acos(-normal.y) / pi;
    return vec2(x, y);
}
