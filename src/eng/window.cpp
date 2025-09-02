#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <eng/main.hpp>
#include <eng/window.hpp>
#include <eng/vectors.hpp>
#include <filesystem>

eng::window_t::window_t(): 
	m_screen(1920, 16.f/9.f) {
	sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();
	this->create(video_mode, "Raytracer", sf::Style::Fullscreen);
	this->setFramerateLimit(60);

	this->m_load_fonts();

	this->m_load_shader();	
}

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

void eng::window_t::m_add_texture(std::string name) {
	sf::Texture texture;
	texture.loadFromFile("./bin/textures/" + name + ".jpg");
	std::pair<std::string, sf::Texture> pair(name + "_texture", texture);	
	this->m_textures.insert(pair);
}

void eng::window_t::m_load_shader() {
        this->m_raytracer.loadFromFile("./shaders/compiled_shader.glsl", sf::Shader::Fragment);

	this->m_raytracer.setUniform("resolution", (sf::Vector2f)this->m_screen.resolution);

	namespace fs = std::filesystem;
	for (auto file: fs::directory_iterator("./bin/textures/")) {
		std::string filename = file.path().filename().string();
		std::string name = filename.substr(0, filename.find_last_of('.'));
		this->m_add_texture(name);
	}
	for (const auto& texture: this->m_textures) {
		this->m_raytracer.setUniform(texture.first, texture.second);
	}
}

void eng::window_t::m_load_fonts() {
	this->m_font.loadFromFile("./bin/fonts/clacon2.ttf");
	this->m_fps.setFont(this->m_font);
	this->m_fps.setCharacterSize(24);
	this->m_fps.setFillColor(sf::Color(255, 0, 255));
	this->m_fps.setPosition(10, 10);
}

void render_shader_to(const sf::Shader& raytracer, eng::screen_t& screen) {
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

	this->m_raytracer.setUniform("delta_time", eng::delta_time);

	render_shader_to(this->m_raytracer, this->m_screen);	
	this->draw(this->m_screen.sprite);

	this->m_fps.setString("fps: " + std::to_string(int(1/eng::delta_time)));
	this->draw(this->m_fps);

	this->display();
}

void eng::window_t::screenshot() {
	namespace fs = std::filesystem;

	unsigned int screenshot_id = 0; 
	for (auto file: fs::directory_iterator("./bin/screenshots/")) {
		screenshot_id++;
	}

	sf::Image image = this->m_screen.texture.getTexture().copyToImage();
	image.saveToFile("./bin/screenshots/" + std::to_string(screenshot_id) + ".png");
}
