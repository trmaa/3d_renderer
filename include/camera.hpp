#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <eng/vectors.hpp>

class camera_t {
private:
	glm::vec3 m_position;
	glm::vec2 m_angle;

	float m_mouse_sensitivity;
	sf::Vector2f m_center_position;
	bool m_mouse_locked;
public:
	sf::Vector3f get_position() { return eng::to_sf_vec3(this->m_position); }
	sf::Vector2f get_angle() { return eng::to_sf_vec2(this->m_angle); }

private:
        void m_lock_mouse();
	void m_handle_mouse_movement();
public:
	void pass_data_to_shader();
	void move();

public:
        camera_t();
};

#endif
