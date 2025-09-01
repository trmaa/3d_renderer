#include <SFML/Graphics.hpp>
#include <eng/main.hpp>

eng::window_t eng::window;

void eng::start_loop() {
	while (eng::window.isOpen()) {
		sf::Event event;
		while (eng::window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				eng::window.close();
		}
		eng::loop();		
	}
}
