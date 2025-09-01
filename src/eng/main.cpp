#include <SFML/Graphics.hpp>
#include <eng/main.hpp>

eng::window_t eng::window;
float eng::delta_time;

void eng::start_loop() {
	sf::Clock clock;
	while (eng::window.isOpen()) {
		sf::Event event;
		while (eng::window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				eng::window.close();
		}
		eng::delta_time = clock.getElapsedTime().asSeconds();
                clock.restart();

		eng::loop();		
	}
}
