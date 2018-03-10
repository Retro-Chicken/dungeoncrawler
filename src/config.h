#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>

namespace config {
	//	Size of the view port of the user.
	extern unsigned VIEW_HEIGHT;
	extern unsigned VIEW_WIDTH;

	//	Primary font of the game.
	extern sf::Font MAIN_FONT;

	//	Events produced by the game window so that all classes may access them.
	extern std::vector<sf::Event> windowEvents;

	//	Function to configure basic settings.
	bool initialize();

	//	Function to load data from configuration file.
	bool load_config_file();
};

#endif
