#include <SFML/Graphics.hpp>
#include <eng/main.hpp>

void eng::loop() {
        eng::window.render();
}

int main() {
	eng::start_loop();

	eng::window.set_uniform("camera_position", sf::Vector3f(0, 0, 10));
	eng::window.set_uniform("camera_angle", sf::Vector2f(3.14159, 0)); //(0,0,-1) righthanded
}
