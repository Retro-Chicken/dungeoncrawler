#include "tools.h"

namespace decorations {
	const sf::IntRect wall::WALL = sf::IntRect(0, 16, 16, 32);
	const sf::IntRect floor::FLOOR = sf::IntRect(0, 64, 16, 16);
	const sf::IntRect banner::BANNER = sf::IntRect(288, 128, 16, 32);
	const sf::IntRect torch::TORCH = sf::IntRect(176, 254, 16, 32);

	wall::wall(int index) : drawable(&params::tileTexture, sf::IntRect(WALL.left + WALL.width * (index % COLUMNS),
		WALL.top + WALL.height * (index/COLUMNS), WALL.width, WALL.height), 0) {
		tag = "wall";
	}

	floor::floor(int index) : drawable(&params::tileTexture, sf::IntRect(FLOOR.left + FLOOR.width * (index % COLUMNS),
		FLOOR.top + FLOOR.height * (index/COLUMNS), FLOOR.width, FLOOR.height), 0) {
		tag = "floor";
	}

	banner::banner(int index) : drawable(&params::tileTexture, sf::IntRect(BANNER.left + BANNER.width * (index % COLUMNS),
		BANNER.top + BANNER.height * (index/COLUMNS), BANNER.width, BANNER.height), 1) {
		tag = "banner";
	}

	torch::torch() : animation(&params::tileTexture, TORCH, COLUMNS, COUNT, 0.5, 1) {
		tag = "torch";
	}
};
