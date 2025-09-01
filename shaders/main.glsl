#version 330 core

uniform vec2 resolution;
uniform vec3 camera_position;
uniform vec2 camera_angle;

vec3 default_col = vec3(0, 0.2, 0.3);

#include "vectors.glsl"

void main() {
        vec3 color = default_col;

	vec2 uv = gl_FragCoord.xy / resolution;
	uv = uv * 2.0 - 1.0;

	vec3 idle_ray_direction = normalize(vec3(uv.x, uv.y, -1.0)); //righthanded
        vec3 ray_direction = angle2_to_vector3_matrix(camera_angle) * idle_ray_direction;

	color = ray_direction;

        gl_FragColor = vec4(color, 1.0);
}
