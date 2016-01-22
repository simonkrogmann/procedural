// return samples * samples location (maximum: 25)
vec2[25] multisampleLocations(vec2 uv, int samples)
{
    vec2 locations[25];
    for (int x = 0;  x < samples; ++x)
    {
        for (int y = 0;  y < samples; ++y)
        {
            locations[x + samples * y] = uv + dFdx(uv) * vec2(x, y) / samples;
        }
    }
    return locations;
}
