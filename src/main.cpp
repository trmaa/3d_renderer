#include <SFML/Graphics.hpp>
#include <cstdio>
#include <eng/main.hpp>
#include "camera.hpp"

camera_t camera;

void eng::loop() {
        eng::window.render();

	eng::window.set_uniform("camera_position", camera.get_position());
	eng::window.set_uniform("camera_angle", camera.get_angle());

	std::printf("camera position: %f %f %f\n", camera.get_position().x, camera.get_position().y, camera.get_position().z);
        //std::printf("camera angle: %f %f\n", camera.get_angle().x, camera.get_angle().y);

        camera.move();
}

int main() {
	eng::start_loop();
}
