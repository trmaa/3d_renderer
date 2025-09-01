#version 330 core

uniform vec2 resolution;

vec3 default_col = vec3(0, 0.2, 0.3);

void main() {
        vec3 color = default_col;

	vec2 uv = gl_FragCoord.xy / resolution;
	uv = uv * 2.0 - 1.0;
        //uv.y = 1.0 - uv.y;

	color = vec3(abs(uv.x), abs(uv.y), 0.0);

        gl_FragColor = vec4(color, 1.0);
}
