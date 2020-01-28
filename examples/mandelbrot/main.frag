void main()
{
    vec2 uv = scaleToCenterSquare(normalizedCoord, iResolution);
    uv = 2.5 * (uv - 0.5);
    uv = rotate(uv, iTime / 10);
    float c = 0.0;
    int samples = 3;
    vec2 array[] = multisampleLocations(uv, samples);
    // super sample to avoid temporal aliasing
    for (int i = 0;  i < samples * samples; ++i)
    {
        c += highlightCenter(mandelbrot(array[i]));
    }
    c /= samples * samples;
    fragColor = vec4(c * vec3(1, 0.3, 0.1), 1.0);
}
