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

struct ray_t {
    vec3 origin;
    vec3 direction;
    float far;
};

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

struct triangle_t {
    vec3 p1;
    vec3 p2;
    vec3 p3;
    vec3 color;
    float roughness;
};

vec3 triangle_normal(triangle_t triangle, ray_t ray) {
    float dotp = dot(cross(triangle.p2, triangle.p3), ray.direction);
    if (dotp > 0) {
        return cross(triangle.p3, triangle.p2);
    }
    return cross(triangle.p2, triangle.p3);
}

float triangle_check_collision(triangle_t triangle, ray_t ray) {
    float denominator = dot(ray.direction, triangle_normal(triangle, ray));

    if (abs(denominator) > 0) { 
        vec3 diff = triangle.p1 - ray.origin;
        float t = dot(diff, triangle_normal(triangle, ray)) / denominator;
        
        vec3 hitp = ray.direction * t + ray.origin;
        
        vec3 v0 = triangle.p2;
        vec3 v1 = triangle.p3;
        vec3 v2 = hitp - triangle.p1;

        float d00 = dot(v0, v0);
        float d01 = dot(v0, v1);
        float d11 = dot(v1, v1);
        float d20 = dot(v2, v0);
        float d21 = dot(v2, v1);
        float denom = d00 * d11 - d01 * d01;

        float v = (d11 * d20 - d01 * d21) / denom;
        float w = (d00 * d21 - d01 * d20) / denom;
        float u = 1.0 - v - w;

        bool cond = (u >= 0.0) && (v >= 0.0) && (w >= 0.0);
        if (cond && t >= 0.0) {
            return t;
        }
    }

    return -1.0;
}


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
