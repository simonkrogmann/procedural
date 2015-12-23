bool insideSquare(vec2 uv)
{
    return 0 <= uv.x && uv.x <= 1 && 0 <= uv.y && uv.y <= 1;
}

vec2 scaleToCenterSquare(vec2 uv, vec2 windowSize) {
    vec2 factor = vec2(
        windowSize.y / windowSize.x,
        windowSize.x / windowSize.y);
    factor = min(factor, 1);
    return (uv - 1.0/2) / factor + 1.0/2;
}

vec3 chess(vec2 uv, int size)
{
    vec2 field = floor(uv * size);
    float color = mod(field.x + field.y, 2);
    return vec3(color);
}

vec3 chessSquare(vec2 uv, vec2 windowSize, int size)
{
    vec2 centerUV = scaleToCenterSquare(uv, windowSize);
    return insideSquare(centerUV) ? chess(centerUV, size) : vec3(0);
}
