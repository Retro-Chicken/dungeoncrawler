#include "config.h"

namespace config {
	unsigned WINDOW_HEIGHT = 20 * 9 * 2 * 2;
	unsigned WINDOW_WIDTH = 20 * 16 * 2 * 2;

	unsigned VIEW_HEIGHT = 20 * 9 * 2;
	unsigned VIEW_WIDTH = 20 * 16 * 2;

	unsigned TILE_SIZE = 16;

	sf::Font MAIN_FONT;

	std::vector<sf::Event> windowEvents;

	sf::RenderWindow* WINDOW = nullptr;
};

void config::setWindow(sf::RenderWindow* window) {
	WINDOW = window;
}

bool config::initialize() {
	MAIN_FONT.loadFromFile("resources/fonts/arial.ttf");
	return true;
}

bool config::load_config_file() {
	return true;
}
