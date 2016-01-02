vec3 chess(vec2 uv, int size)
{
    vec2 field = floor(uv * float(size));
    float color = mod(field.x + field.y, 2.0);
    return vec3(color);
}

vec3 chessSquare(vec2 uv, int size, vec2 windowSize)
{
    vec2 centerUV = scaleToCenterSquare(uv, windowSize);
    return insideSquare(centerUV) ? chess(centerUV, size) : vec3(0);
}
