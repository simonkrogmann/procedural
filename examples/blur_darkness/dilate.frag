const float similar_threshold = 0.01f;

float sample_distances[] = float[](0.0005, 0.001, 0.002, 0.003, 0.004, 0.005, 0.007, 0.01);
vec2 sample_directions[8] = vec2[](
    vec2(1.0, 0.0), vec2(-1.0, 0.0),
    vec2(0.0, 1.0), vec2(0.0, -1.0),
    vec2(1.0, 1.0), vec2(-1.0, -1.0),
    vec2(1.0, -1.0), vec2(-1.0, 1.0)
);

void main() {
    int white = 0;
    vec3 reference = vec3(1.0);
    float pixel = texture(color_range, normalizedCoord).r;
    for (int dir = 0; dir < 8; ++dir) {
        for (int i = 0; i < 8; ++i) {
            vec2 sample_point = sample_directions[dir] * sample_distances[i];

            vec3 sample_value = texture(color_range, normalizedCoord + sample_point).rgb;
            float difference = dot(vec3(1), abs(reference - sample_value));
            if (difference < similar_threshold) {
                ++white;
                break;
            }
        }
    }
    if (white > 6 || pixel > 0.9) {
        fragColor = vec4(1.0, 1.0, 1.0, 1.0);
    } else {
        fragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
