#ifndef ENG_WINDOW_HPP
#define ENG_WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace eng {
	struct screen_t {
		sf::Vector2u resolution;
		sf::RenderTexture texture;
		sf::Sprite sprite;

		screen_t(unsigned int resolution, float aspect_ratio);
	};

	class window_t: public sf::RenderWindow {
	private:
		eng::screen_t m_screen;
		sf::Shader m_raytracer;

		sf::Font m_font;
		sf::Text m_fps;
	public:
		sf::Vector2u resolution() { return this->m_screen.resolution; }
                sf::Color default_col() { return sf::Color(255, 255, 255); }

	private:
	public:
		template <typename any_t>
		void set_uniform(const std::string& name, const any_t& value) {
			this->m_raytracer.setUniform(name, value);
		}

		void render();

        public:
		window_t();
	};
}

#endif
