#version 330 core

//engin
uniform vec2 resolution;
uniform sampler2D sky_texture;

mat3 angle2_to_vector3_matrix(vec2 angle) {
    float pitch = angle.x;
    float yaw = angle.y;
    
    float cos_pitch = cos(pitch);
    float sin_pitch = sin(pitch);
    float cos_yaw = cos(yaw);
    float sin_yaw = sin(yaw);
    
    return mat3(
        cos_yaw, 0.0, -sin_yaw,
        sin_yaw * sin_pitch, cos_pitch, cos_yaw * sin_pitch,
        sin_yaw * cos_pitch, -sin_pitch, cos_yaw * cos_pitch
    );
}

vec3 sphere_color_at(vec3 normal) {
    float theta = acos(normal.y);
    float phi = atan(normal.z, normal.x);

    float u = (phi + 3.14159) / (2.0 * 3.14159);
    float v = theta / 3.14159;

    vec3 color = texture(sky_texture, vec2(u, v)).rgb;
    return color;
}


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
