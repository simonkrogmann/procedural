void main() {
    vec2 uv = scaleToCenterSquare(position, windowSize);

    uv = uv * 2 - 1;
    uv *= 0.5;
    uv = uv * 0.5 + 0.5;

    color = raindrops(blur_y, uv, 0.5);
}
