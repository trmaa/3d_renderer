#include <eng/main.hpp>
#include "camera.hpp"

camera_t::camera_t() {
        this->m_position = glm::vec3(0.0f, 0.0f, 10.0f);
        this->m_angle = glm::vec2(0.f, 0.f); // (0,0,-1) righthanded (elevation angle, angle arround y axis)

        this->m_mouse_sensitivity = 0.2f;
        this->m_mouse_locked = false;

	this->m_lock_mouse();
}

void camera_t::m_lock_mouse() {
	this->m_center_position = sf::Vector2f(eng::window.getSize().x / 2.f, eng::window.getSize().y / 2.f);
	eng::window.setMouseCursorVisible(false);
	sf::Mouse::setPosition(
		eng::window.mapCoordsToPixel({ this->m_center_position.x, this->m_center_position.y }), 
		eng::window);
	this->m_mouse_locked = true;
}

void camera_t::m_handle_mouse_movement() {
        if (!this->m_mouse_locked) {
            this->m_lock_mouse();
            return;
        }

        sf::Vector2f mouse_position = (sf::Vector2f)sf::Mouse::getPosition(eng::window);
        sf::Vector2f mouse_delta = mouse_position - this->m_center_position;

        this->m_angle.y -= mouse_delta.x * this->m_mouse_sensitivity * 0.0174533f;
        this->m_angle.x -= mouse_delta.y * this->m_mouse_sensitivity * 0.0174533f;

        sf::Mouse::setPosition(
		eng::window.mapCoordsToPixel({ this->m_center_position.x, this->m_center_position.y }), 
		eng::window);
}

void camera_t::move() {
	this->m_handle_mouse_movement();

	float fixed_speed = 1.0f * eng::delta_time;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		fixed_speed *= 10;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->m_position.x -= std::sin(this->m_angle.y) * fixed_speed;
		this->m_position.z -= std::cos(this->m_angle.y) * fixed_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->m_position.x += std::sin(this->m_angle.y) * fixed_speed;
		this->m_position.z += std::cos(this->m_angle.y) * fixed_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->m_position.x += std::sin(this->m_angle.y - 3.14159f/2.f) * fixed_speed;
		this->m_position.z += std::cos(this->m_angle.y - 3.14159f/2.f) * fixed_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->m_position.x -= std::sin(this->m_angle.y - 3.14159f/2.f) * fixed_speed;
		this->m_position.z -= std::cos(this->m_angle.y - 3.14159f/2.f) * fixed_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		this->m_position.y += fixed_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		this->m_position.y -= fixed_speed;
	}
}
