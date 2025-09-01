#ifndef ENG_MAIN_HPP
#define ENG_MAIN_HPP

#include <SFML/Graphics.hpp>
#include <eng/window.hpp>

namespace eng {
	extern eng::window_t window;

	void loop();

	void start_loop(); 
}

#endif
