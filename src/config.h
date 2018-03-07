#include <SFML\Graphics.hpp>

#ifndef CONFIG_H
#define CONFIG_H

namespace config {
	extern unsigned VIEW_HEIGHT;
	extern unsigned VIEW_WIDTH;

	extern sf::Font MAIN_FONT;

	bool load_config_file();
}

#endif
