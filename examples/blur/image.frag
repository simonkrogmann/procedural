vec3 colorFunc(float factor)
{
    factor = abs((factor - 0.5) * 2);
    return pow((1.0 - factor), 0.6) * vec3(1, 0.3, 0.1);
}

void main()
{
    vec2 uv = scaleToCenterSquare(position, windowSize);
    uv = 2.5 * (uv - 0.5);
    vec3 c = colorFunc(mandelbrot(uv));

    color = vec4(c, 1.0);
}
