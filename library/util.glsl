bool insideSquare(vec2 uv)
{
    return 0 <= uv.x && uv.x <= 1 && 0 <= uv.y && uv.y <= 1;
}

vec2 scaleToCenterSquare(vec2 uv, vec2 windowSize)
{
    vec2 factor = vec2(
        windowSize.y / windowSize.x,
        windowSize.x / windowSize.y);
    factor = min(factor, 1);
    return (uv - 1.0/2) / factor + 1.0/2;
}

float aastep(float threshold, float value)
{
    float xdiff = dFdx(value);
    float ydiff = dFdy(value);
    float delta = 0.7 * length(vec2(xdiff, ydiff));

    return smoothstep(threshold - delta, threshold + delta, value);
}
