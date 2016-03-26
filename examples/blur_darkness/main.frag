const float similar_threshold = 0.8;

void main() {

    vec3 image_color = texture(image, position).rgb;
    vec3 blur_color = texture(blur_y, position).rgb;
    float dilate_color = texture(blur_yd, position).r;
    color = vec4(mix(blur_color, image_color, dilate_color), 1.0);
}
