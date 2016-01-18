float mandelbrot(vec2 position)
{
    vec2 c = vec2(0.0);
    int iteration = 0;
    int max_iterations = 256;
    while (iteration < max_iterations && dot(c, c) < 5.0)
    {
        vec2 new = vec2(c.x * c.x - c.y * c.y, 2.0*c.x*c.y) + position;
        c = new;
        ++iteration;
    }
    return float(iteration) / float(max_iterations);
}
