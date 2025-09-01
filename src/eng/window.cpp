#include <SFML/Graphics.hpp>
#include <eng/window.hpp>

eng::screen_t::screen_t(unsigned int resolution, float aspect_ratio) {
	this->resolution = sf::Vector2u(resolution, resolution * aspect_ratio);

	this->texture.create(this->resolution.x, this->resolution.y);
        this->texture.setSmooth(true);

        this->sprite.setTexture(this->texture.getTexture());
}

eng::window_t::window_t(): 
	m_screen(1280, 16.0f / 9.0f) {
	float aspect_ratio = this->m_screen.resolution.y / (float)this->m_screen.resolution.x;
	unsigned int resolution = this->m_screen.resolution.x;

	sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();
	this->create(video_mode, "Raytracer", sf::Style::Fullscreen);

	this->m_raytracer.loadFromFile("./shaders/compiled_shader.glsl", sf::Shader::Fragment);

	this->setFramerateLimit(60);
}

void eng::window_t::render() {
	this->clear(this->default_col());
        this->display();
}
