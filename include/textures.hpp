#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

extern std::map<std::string, sf::Texture> g_textures;

static void add_texture(std::string name);

void g_load_textures();

#endif
