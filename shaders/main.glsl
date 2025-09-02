#version 330 core

//engin
uniform vec2 resolution;
uniform sampler2D sky_texture;

#include "vector.glsl"
#include "sphere.glsl"

vec3 default_col = vec3(0, 0.2, 0.3);

//program
uniform vec3 camera_position;
uniform vec2 camera_angle;

void main() {
	vec2 uv = gl_FragCoord.xy / resolution;
	uv = uv * 2.0 - 1.0;

	vec3 idle_ray_direction = normalize(vec3(uv.x, uv.y, -1.0)); //righthanded
        vec3 ray_direction = angle2_to_vector3_matrix(camera_angle) * idle_ray_direction;

	vec3 color = ray_direction;

	//ray tracing

	color = sphere_color_at(ray_direction);

	//end ray tracing

        gl_FragColor = vec4(color, 1.0);
}
