bool insideSquare(vec2 uv)
{
    return 0.0 <= uv.x && uv.x <= 1.0 && 0.0 <= uv.y && uv.y <= 1.0;
}

vec2 scaleToCenterSquare(vec2 uv, vec2 windowSize)
{
    vec2 factor = vec2(
        windowSize.y / windowSize.x,
        windowSize.x / windowSize.y);
    factor = min(factor, 1.0);
    return (uv - 0.5) / factor + 0.5;
}

float aastep(float threshold, float value)
{
    float xdiff = dFdx(value);
    float ydiff = dFdy(value);
    float delta = 0.7 * length(vec2(xdiff, ydiff));

    return smoothstep(threshold - delta, threshold + delta, value);
}

vec2 rotate(vec2 uv, float angle)
{
    mat2 rotation = mat2(
        cos(angle), -sin(angle),
        sin(angle), cos(angle)
    );
    return rotation * uv;
}
