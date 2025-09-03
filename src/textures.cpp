#include <filesystem>
#include <eng/main.hpp>
#include "textures.hpp"

std::map<std::string, sf::Texture> g_textures;

static void add_texture(std::string name) {
	sf::Texture texture;
	texture.loadFromFile("./bin/textures/" + name + ".jpg");
	std::pair<std::string, sf::Texture> pair(name + "_texture", texture);	
	g_textures.insert(pair);
}

void g_load_textures() {
	namespace fs = std::filesystem;
	for (auto file: fs::directory_iterator("./bin/textures/")) {
		std::string filename = file.path().filename().string();
		std::string name = filename.substr(0, filename.find_last_of('.'));
		add_texture(name);
	}
	for (const auto& texture: g_textures) {
		eng::window.set_uniform(texture.first, texture.second);
	}
}
