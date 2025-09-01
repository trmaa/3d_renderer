#ifndef ENG_WINDOW_HPP
#define ENG_WINDOW_HPP

#include <SFML/Graphics.hpp>

namespace eng {
	struct screen_t {
		sf::Vector2u resolution;
		sf::RenderTexture texture;
		sf::Sprite sprite;
		sf::RectangleShape shape;

		screen_t(unsigned int resolution, float aspect_ratio);
	};

	class window_t: public sf::RenderWindow {
	private:
		eng::screen_t m_screen;
		sf::Shader m_raytracer;
	public:
		sf::Vector2u resolution() { return this->m_screen.resolution; }
                sf::Color default_col() { return sf::Color(255, 255, 255); }

	private:
	public:
		void render();

        public:
		window_t();
	};
}

#endif
