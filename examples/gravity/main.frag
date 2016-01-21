void main()
{
    vec2 uv = scaleToCenterSquare(position, windowSize);
    vec2 force = vec2(0.0);
    for (int i = 0; i < numBodies; ++i)
    {
        vec2 point = points[i];
        if (i != 0)
        {
            point = rotate(point, time / i);
        }
        point += 0.5;
        float magnitude = gravity[i] / pow(distance(uv, point), 2);
        force += magnitude * normalize(point - uv);
    }


    float scaled = log(length(force)) * 2;
    color = vec4(colorSin(scaled), 1.0);
}
