#ifndef ENG_VECTORS_HPP
#define ENG_VECTORS_HPP

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

namespace eng {
        inline glm::vec2 to_glm(sf::Vector2u vector) {
                return glm::vec2(vector.x, vector.y);
        }

	inline sf::Vector2f to_sfml(glm::vec2 vector) {
                return sf::Vector2f(vector.x, vector.y);
        }
}

#endif
