float random(vec3 seed) {
    return fract(sin(dot(seed /*+ vec3(iTime)*/, vec3(12.9898, 78.233, 45.164))) * 43758.5453);
}
