float diffuse(vec3 normal, vec3 light)
{
    float factor = dot(normal, light);
    return clamp(factor, 0, 1);
}

float specular(vec3 reflection, vec3 eye, float alpha)
{
    float factor = pow(dot(reflection, eye), alpha);
    return clamp(factor, 0, 1);
}

float ambient()
{
    return 1;
}

float phong(vec3 normal, vec3 light, vec3 eye, vec4 factors)
{
    vec3 reflection = -reflect(light, normal);
    return factors.x * ambient() + factors.y * diffuse(normal, light)
        + factors.z * specular(reflection, eye, factors.w);
}
