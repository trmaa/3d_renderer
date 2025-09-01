#include <SFML/Graphics.hpp>
#include <eng/main.hpp>

void eng::loop() {
        eng::window.render();
}

int main() {
	eng::start_loop();
}
