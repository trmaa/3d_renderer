#ifndef ENG_VECTORS_HPP
#define ENG_VECTORS_HPP

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

namespace eng {
	template<typename T>
	glm::tvec2<T> to_glm_vec2(const sf::Vector2<T>& sf_vec) {
		return glm::tvec2<T>(sf_vec.x, sf_vec.y);
	}

	template<typename T>
	glm::tvec3<T> to_glm_vec3(const sf::Vector3<T>& sf_vec) {
		return glm::tvec3<T>(sf_vec.x, sf_vec.y, sf_vec.z);
	}

	template<typename T>
	sf::Vector2<T> to_sf_vec2(const glm::tvec2<T>& glm_vec) {
		return sf::Vector2<T>(glm_vec.x, glm_vec.y);
	}

	template<typename T>
	sf::Vector3<T> to_sf_vec3(const glm::tvec3<T>& glm_vec) {
		return sf::Vector3<T>(glm_vec.x, glm_vec.y, glm_vec.z);
	}

	inline glm::ivec2 to_glm_vec2(const sf::Vector2i& sf_vec) {
		return glm::ivec2(sf_vec.x, sf_vec.y);
	}

	inline glm::vec2 to_glm_vec2(const sf::Vector2f& sf_vec) {
		return glm::vec2(sf_vec.x, sf_vec.y);
	}

	inline glm::vec2 to_glm_vec2(const sf::Vector2u& sf_vec) {
		return glm::vec2(static_cast<float>(sf_vec.x), static_cast<float>(sf_vec.y));
	}

	inline sf::Vector2i to_sf_vec2i(const glm::ivec2& glm_vec) {
		return sf::Vector2i(glm_vec.x, glm_vec.y);
	}

	inline sf::Vector2f to_sf_vec2f(const glm::vec2& glm_vec) {
		return sf::Vector2f(glm_vec.x, glm_vec.y);
	}

	inline sf::Vector2u to_sf_vec2u(const glm::uvec2& glm_vec) {
		return sf::Vector2u(glm_vec.x, glm_vec.y);
	}
}

#endif
