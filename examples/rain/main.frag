void main() {
    vec2 uv = scaleToCenterSquare(normalizedCoord, iResolution);

    uv = uv * 2 - 1;
    uv *= 0.5;
    uv = uv * 0.5 + 0.5;

    fragColor = raindrops(blur_y, uv, 0.5);
}
