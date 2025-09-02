#version 330 core

//engin
uniform vec2 resolution;
uniform sampler2D sky_texture; //texture names are the ones at bin/texutres
uniform sampler2D earth_texture;

#include "vector.glsl"
#include "sphere.glsl"

vec3 default_col = vec3(0, 0.2, 0.3);

//program
uniform vec3 camera_position;
uniform vec2 camera_angle;
uniform float FAR;

void main() {
	vec2 uv = gl_FragCoord.xy / resolution;
	uv = uv * 2.0 - 1.0;

	vec3 idle_ray_direction = normalize(vec3(uv.x*16, uv.y*9, FAR)); //righthanded 0 pitch 0 yaw means 0 0 -1
        vec3 ray_direction = angle2_to_vector3_matrix(camera_angle) * idle_ray_direction;
	ray_direction = normalize(ray_direction);

	vec3 color = ray_direction;

	//ray tracing

	color = sphere_color_at(sky_texture, ray_direction);

	float colided = sphere_check_collision(camera_position, ray_direction);
        if (colided > 0) {
		vec3 normal = ray_direction * colided + camera_position; 
		float brightness = dot(normal, vec3(1,1,0));
		color = sphere_color_at(earth_texture, normal) * (vec3(brightness)/3 + vec3(2)/3);
        }

	//end ray tracing

        gl_FragColor = vec4(color, 1.0);
}
