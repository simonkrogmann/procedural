void main()
{
    vec2 uv = scaleToCenterSquare(position, windowSize);
    uv = 2.5 * (uv - 0.5);
    uv = rotate(uv, time / 10);
    float c = 0.0;
    int samples = 3;
    vec2 array[] = multisampleLocations(uv, samples);
    // super sample to avoid temporal aliasing
    for (int i = 0;  i < samples * samples; ++i)
    {
        c += highlightCenter(mandelbrot(array[i]));
    }
    c /= samples * samples;
    color = vec4(c * vec3(1, 0.3, 0.1), 1.0);
}
