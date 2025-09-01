#version 330 core

test
test
test
test
test
test
test

test2
test2
test2
test2
test2
test2
test2


vec3 default_col = vec3(0, 0.2, 0.3);

void main() {
        vec3 color = default_col;

        gl_FragColor = vec4(color, 1.0);
}
