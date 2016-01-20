float weight(float sigma, float factor, int i)
{
    return factor * pow(e, -0.5 * pow(i / sigma, 2.0));
}

vec4 blurX(sampler2D image, vec2 uv, int samples)
{
    vec4 accum = vec4(0.0);
    float sigma = float(samples) / 3.0;
    float factor = 1.0 / (sigma * sqrt(2.0 * pi));
    float weightAccum = 0.0;
    for (int i = -samples; i <= samples; ++i)
    {
        float weight = weight(sigma, factor, i);
        accum += weight * textureOffset(image, uv, ivec2(i, 0));
        weightAccum += weight;
    }
    return accum / weightAccum;
}

vec4 blurY(sampler2D image, vec2 uv, int samples)
{
    vec4 accum = vec4(0.0);
    float sigma = float(samples) / 3.0;
    float factor = 1.0 / (sigma * sqrt(2.0 * pi));
    float weightAccum = 0.0;
    for (int i = -samples; i <= samples; ++i)
    {
        float weight = weight(sigma, factor, i);
        accum += weight * textureOffset(image, uv, ivec2(0, i));
        weightAccum += weight;
    }
    return accum / weightAccum;
}

