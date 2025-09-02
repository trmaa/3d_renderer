vec3 sphere_color_at(sampler2D textur, vec3 normal) {
	float theta = acos(normal.y);
	float phi = atan(-normal.z, normal.x);

	float u = (phi + 3.14159) / (2.0 * 3.14159);
	float v = theta / 3.14159;

	vec4 color = texture(textur, vec2(u, v));
	return color.rgb;
}

float sphere_check_collision(ray_t ray) {
	float radius = 1;  

	vec3 oc = ray.origin;
	float a = dot(ray.direction, ray.direction);
	float b = 2.0 * dot(oc, ray.direction);
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4.0 * a * c;

	if (discriminant < 0.0) {
		return -1.0;  
	} else {
		float t1 = (-b - sqrt(discriminant)) / (2.0 * a);
		float t2 = (-b + sqrt(discriminant)) / (2.0 * a);
		return (t1 > 0.0) ? t1 : t2;
	}
}
