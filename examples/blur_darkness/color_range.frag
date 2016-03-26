void main() {
    vec3 image_color = texture(image, position).rgb;
    vec3 reference = vec3(0.0, 0.0, 0.0);
    float difference = dot(vec3(1.0), abs(image_color - reference));
    if (difference > 1.0) {
        color = vec4(vec3(1.0), 1.0);
    } else {
        color = vec4(vec3(0.0), 1.0);
    }
}
