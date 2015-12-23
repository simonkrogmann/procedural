vec3 chess(vec2 uv, int size)
{
    vec2 field = floor(uv * size);
    float color = mod(field.x + field.y, 2);
    return vec3(color);
}
