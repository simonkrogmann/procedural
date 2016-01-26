void main()
{
    vec2 uv = scaleToCenterSquare(position, windowSize);
    vec4 sphereData = sphere(uv, spherePos, size);

    vec3 normal = rotateY(sphereData.xyz, pi);
    normal = rotateY(normal, time / 10);
    vec2 texCoords = polar(normal);
    vec3 sun = rotateY(light, time / 10);

    vec3 dayColor = texture(day, texCoords).rgb;
    vec3 nightColor = 0.7 * texture(night, texCoords).rgb;
    vec3 starsColor = 2 * texture(stars, uv).rgb;

    float intensity = phong(sphereData.xyz, sun, eye, factors);
    vec3 earthColor = mix(nightColor, dayColor, intensity);

    float dist = length(uv - spherePos);

    float atmos = smoothstep(size - 0.02, size + 0.02, dist);
    atmos = highlightCenter(atmos);

    color = vec4(mix(mix(starsColor, earthColor, sphereData.a), intensity * horizon, atmos), 1.0);
}
