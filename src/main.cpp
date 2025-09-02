#include <SFML/Graphics.hpp>
#include <eng/main.hpp>
#include "camera.hpp"

camera_t camera;

void eng::loop() {
        camera.move();
	eng::window.set_uniform("camera_position", camera.get_position());
	eng::window.set_uniform("camera_angle", camera.get_angle());

        eng::window.render();	
}

int main() {
	eng::start_loop();
}
