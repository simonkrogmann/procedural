float diffuse(vec3 normal, vec3 light)
{
    float factor = dot(normal, light);
    return clamp(factor, 0.0, 1.0);
}

float specular(vec3 reflection, vec3 eye, float alpha)
{
    float factor = clamp(dot(reflection, eye), 0.0, 1.0);
    return pow(factor, alpha);
}

float ambient()
{
    return 1.0;
}

float phong(vec3 normal, vec3 light, vec3 eye, vec4 factors)
{
    vec3 reflection = -reflect(light, normal);
    return factors.x * ambient() + factors.y * diffuse(normal, light)
        + factors.z * specular(reflection, eye, factors.w);
}
