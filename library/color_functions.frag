vec3 colorSin(float value)
{
    // add values to align peaks
    vec3 result =  vec3(
        sin(value * 4),
        sin(value * 2 + 0.5),
        sin(value + 0.75));

    // scale to [0, 1]
    return result / 2.0 + 0.5;
}

float highlightCenter(float factor)
{
    // input should be in [0, 1]
    // return (distance to 0.5) / 2
    factor = abs((factor - 0.5) * 2);
    return 1.0 - factor;
}
