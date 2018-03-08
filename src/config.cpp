#include "config.h"

namespace config {
	unsigned VIEW_HEIGHT = 3 * 32 * 2;
	unsigned VIEW_WIDTH = 5 * 32 * 2;

	sf::Font MAIN_FONT;
};

bool config::load_config_file() {
	return true;
}
