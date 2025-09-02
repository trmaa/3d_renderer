#version 330 core

//engin
uniform vec2 resolution;
uniform sampler2D sky_texture; //texture names are the ones at bin/texutres
uniform sampler2D stars_texture;
uniform sampler2D earth_texture;

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

vec3 sphere_color_at(sampler2D textur, vec3 normal) {
	float theta = acos(normal.y);
	float phi = atan(-normal.z, normal.x);

	float u = (phi + 3.14159) / (2.0 * 3.14159);
	float v = theta / 3.14159;

	vec4 color = texture(textur, vec2(u, v));
	return color.rgb;
}

float sphere_check_collision(vec3 ray_origin, vec3 ray_direction) {
	float radius = 1;  

	vec3 oc = ray_origin;
	float a = dot(ray_direction, ray_direction);
	float b = 2.0 * dot(oc, ray_direction);
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

	vec3 color = ray_direction; //default

	//start ray tracing

	color = sphere_color_at(stars_texture, ray_direction);	

	float colision = sphere_check_collision(camera_position, ray_direction);
        if (colision > 0) {
		vec3 normal = ray_direction*colision + camera_position;
                float brightness = dot(normal, vec3(1));
                color = sphere_color_at(earth_texture, normal) * brightness;
        }

	//end ray tracing

        gl_FragColor = vec4(color, 1.0);
}
