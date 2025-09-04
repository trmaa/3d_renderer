#include <SFML/Graphics.hpp>
#include <eng/main.hpp>

eng::window_t eng::window;
float eng::delta_time;

int main() {
	sf::Clock clock;
	if (eng::window.isOpen()) {
		eng::start();
	}
	while (eng::window.isOpen()) {
		sf::Event event;
		while (eng::window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				eng::window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			eng::window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
			eng::window.screenshot();
		}

		eng::delta_time = clock.getElapsedTime().asSeconds();
                clock.restart();

		eng::loop();		
	}
}
