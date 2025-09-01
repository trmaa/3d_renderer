#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <eng/main.hpp>
#include <eng/window.hpp>
#include <eng/vectors.hpp>

eng::screen_t::screen_t(unsigned int resolution, float aspect_ratio) {
	this->resolution = sf::Vector2u(resolution, resolution / aspect_ratio);

	this->texture.create(this->resolution.x, this->resolution.y);
	this->texture.setSmooth(true);

	sf::Vector2f true_resolution = (sf::Vector2f)eng::window.getSize();	
	sf::Vector2f scale = sf::Vector2f(
		true_resolution.x / this->resolution.x, 
		true_resolution.y / this->resolution.y);

        this->sprite.setTexture(this->texture.getTexture());
        this->sprite.setScale(scale);

	this->sprite.setPosition(0, 0);
}

eng::window_t::window_t(): 
	m_screen(1280, 16.f/9.f) {
	float aspect_ratio = this->m_screen.resolution.y / (float)this->m_screen.resolution.x;
	unsigned int resolution = this->m_screen.resolution.x;

	sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();
	this->create(video_mode, "Raytracer", sf::Style::Fullscreen);

	this->m_raytracer.loadFromFile("./shaders/compiled_shader.glsl", sf::Shader::Fragment);

	this->setFramerateLimit(60);
}

void render_shader_to(sf::Shader& raytracer, eng::screen_t& screen) {
	screen.texture.clear(sf::Color(255, 0, 0));
        sf::RectangleShape buffer = sf::RectangleShape((sf::Vector2f)screen.resolution);
	buffer.setPosition(0, 0);
	screen.texture.draw(buffer, &raytracer);
	screen.texture.display();

	float scale_x = eng::window.getSize().x / (float)screen.resolution.x;
	float scale_y = eng::window.getSize().y / (float)screen.resolution.y;
        screen.sprite.setScale(scale_x, scale_y);
        screen.sprite.setPosition(0, 0);
}

void eng::window_t::render() {
	this->clear(this->default_col());

	this->m_raytracer.setUniform("resolution", (sf::Vector2f)this->m_screen.resolution);

	render_shader_to(this->m_raytracer, this->m_screen);	
	this->draw(this->m_screen.sprite);

	this->display();
}
