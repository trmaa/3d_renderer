#version 330 core

uniform vec2 resolution;
uniform vec3 camera_position;
uniform vec2 camera_angle;

vec3 default_col = vec3(0, 0.2, 0.3);

mat3 angle2_to_vector3_matrix(vec2 angle2) {
    float cos_pitch = cos(angle2.y);
    float sin_pitch = sin(angle2.y);
    float cos_yaw = cos(-angle2.x);
    float sin_yaw = sin(-angle2.x);

    mat3 R_x = mat3(
        1, 0, 0,
        0, cos_pitch, -sin_pitch,
        0, sin_pitch, cos_pitch
    );

    mat3 R_y = mat3(
        cos_yaw, 0, sin_yaw,
        0, 1, 0,
        -sin_yaw, 0, cos_yaw
    );

    mat3 R = R_y * R_x;

    return R;
}


void main() {
        vec3 color = default_col;

	vec2 uv = gl_FragCoord.xy / resolution;
	uv = uv * 2.0 - 1.0;

	vec3 idle_ray_direction = normalize(vec3(uv.x, uv.y, -1.0)); //righthanded
        vec3 ray_direction = angle2_to_vector3_matrix(camera_angle) * idle_ray_direction;

	color = ray_direction;

        gl_FragColor = vec4(color, 1.0);
}
