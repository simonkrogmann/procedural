vec3 colorFunc(float factor)
{
    factor = abs((factor - 0.5) * 2);
    return (1.0 - factor) * vec3(1, 0.3, 0.1);
}

void main()
{
    vec2 uv = scaleToCenterSquare(position, windowSize);
    uv = 2.5 * (uv - 0.5);
    uv = rotate(uv, time / 10);
    vec3 c = vec3(0.0);
    int samples = 3;
    vec2 array[] = multisampleLocations(uv, samples);
    for (int i = 0;  i < samples * samples; ++i)
    {
        c += colorFunc(mandelbrot(array[i]));
    }
    c /= samples * samples;
    color = vec4(c, 1.0);
}
