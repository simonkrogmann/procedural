void main()
{
    vec4 sphereData = sphere(position, vec2(0.5, 0.5), 0.4, vec2(windowSize));
    vec3 sphere = phong(sphereData.xyz, light, eye, factors) * sphereColor;
    color = vec4(sphere, 1) * sphereData.a;
}
