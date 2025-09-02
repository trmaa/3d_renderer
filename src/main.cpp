#include <SFML/Graphics.hpp>
#include <eng/main.hpp>
#include "camera.hpp"

camera_t camera;

void eng::loop() {
        camera.move();

        eng::window.render();	
}

int main() {
	eng::start_loop();
}
