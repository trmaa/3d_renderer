#version 330 core

//engin
uniform vec2 resolution;
uniform sampler2D sky_texture; //texture names are the ones at bin/texutres
uniform sampler2D stars_texture;
uniform sampler2D earth_texture;

#include "vector.glsl"
#include "ray.glsl"
#include "sphere.glsl"
#include "triangle.glsl"

//program
uniform vec3 camera_position;
uniform vec2 camera_angle;
uniform float FAR;

void main() {
	vec2 uv = gl_FragCoord.xy / resolution;
	uv = uv * 2.0 - 1.0;

	vec3 idle_ray_direction = normalize(vec3(uv.x*16, uv.y*9, FAR)); //righthanded 0 pitch 0 yaw means 0 0 -1
	ray_t ray;
        ray.direction = angle2_to_vector3_matrix(camera_angle) * idle_ray_direction;
	ray.direction = normalize(ray.direction);
	ray.origin = camera_position;

	vec3 color = ray.direction; //default

	//start ray tracing

	color = sphere_color_at(sky_texture, ray.direction);	

	color = vec3(0, 0.2, 0.3);

	triangle_t triangle;
        triangle.p1 = vec3(0, 0, 0);
        triangle.p2 = vec3(1, 0, 0);
        triangle.p3 = vec3(0, 1, 0);
        triangle.color = vec3(1, 0, 0);
        triangle.roughness = 0.5;

	float t = triangle_check_collision(triangle, ray);
	if (t > 0) {
                vec3 hitp = t * ray.direction + ray.origin;
                vec3 normal = triangle_normal(triangle, ray);
		float brightness = dot(normal, vec3(1));
                color = triangle.color * brightness;
        }

	//end ray tracing

        gl_FragColor = vec4(color, 1.0);
}
