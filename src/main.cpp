#include <SFML/Graphics.hpp>
#include <eng/main.hpp>
#include "camera.hpp"
#include "textures.hpp"

camera_t camera;

void eng::loop() {
        camera.move();
	camera.pass_data_to_shader();

        eng::window.render();	
}

void eng::start() {
	g_load_textures();
}
