vec3 sphere_color_at(vec3 normal) {
    float theta = acos(normal.y);
    float phi = atan(normal.z, normal.x);

    float u = (phi + 3.14159) / (2.0 * 3.14159);
    float v = theta / 3.14159;

    vec3 color = texture(sky_texture, vec2(u, v)).rgb;
    return color;
}
