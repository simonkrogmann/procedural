// uses includes:
//  - math

float weight(float sigma, float factor, int i)
{
    return factor * pow(e, -0.5 * pow(i / sigma, 2.0));
}

vec4 blur(sampler2D image, vec2 uv, int samples, ivec2 resolution, bool horizontal)
{
    vec4 accum = vec4(0.0);
    float sigma = float(samples) / 3.0;
    float factor = 1.0 / (sigma * sqrt(2.0 * pi));
    float weightAccum = 0.0;
    vec2 invResolution = float(1) / vec2(resolution);
    for (int i = -samples; i <= samples; ++i)
    {
        float weight = weight(sigma, factor, i);
        vec2 offset = horizontal ? vec2(i, 0) : vec2(0, i);
        accum += weight * texture(image, uv + invResolution * offset);
        weightAccum += weight;
    }
    return accum / weightAccum;
}

vec4 blurY(sampler2D image, vec2 uv, int samples, ivec2 resolution)
{
    return blur(image, uv, samples, resolution, false);
}

vec4 blurX(sampler2D image, vec2 uv, int samples, ivec2 resolution)
{
    return blur(image, uv, samples, resolution, true);
}

