float dropHeight(vec2 uv)
{
    return snoise(uv * 20.0) * 2.0 - 1.0;
}

vec4 raindrops(sampler2D image, vec2 uv, float scale)
{
    vec2 imageUV = uv;
    vec2 rainUV = uv / scale;
    float waterDropHeight = dropHeight(rainUV);

    vec4 outsideColor = texture(image, imageUV);
    float worldSpaceOffset = 4.0;
    float noiseOffset = 0.001;
    float deltaX = waterDropHeight - dropHeight(rainUV - vec2(noiseOffset, 0.0));
    float deltaY = waterDropHeight - dropHeight(rainUV - vec2(0.0, noiseOffset));
    vec3 x_vec = vec3(worldSpaceOffset, 0.0, deltaX);
    vec3 y_vec = vec3(0.0, worldSpaceOffset, deltaY);
    vec3 waterSurfaceNormal = normalize(cross(x_vec, y_vec));
    vec3 lightDirection = vec3(0.0, 0.0, 1.0);
    float waterAirRefractionIndex = 1.33;
    vec3 result = refract(lightDirection, waterSurfaceNormal, waterAirRefractionIndex);
    vec4 insideColor = textureLod(image, imageUV + result.xy, 3);

    float outsideDrop = aastep(0.0, waterDropHeight);

    return mix(outsideColor, insideColor, outsideDrop);
}
