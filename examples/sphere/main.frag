void main()
{
    float size = abs(mod(time, 10.0) - 5.0) / 10.0;
    vec4 sphereData = sphere(position, vec2(0.5, 0.5), size, vec2(windowSize));
    vec3 sphere = phong(sphereData.xyz, light, eye, factors) * sphereColor;
    color = vec4(sphere, 1.0) * sphereData.a;
}
