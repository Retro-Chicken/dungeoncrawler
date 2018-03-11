#include <SFML/Graphics.hpp>
#include <iostream>
#include "scenes/SceneManager.h"
#include "testscene.h"
#include "config.h"


int main() {
	//	Initialize the configuration file.
	if(!config::initialize())
		cout << "[!] Error initializing configuration.";

	//	Create window for the game.
	sf::RenderWindow window(sf::VideoMode(dungeon::MAP_WIDTH * config::TILE_SIZE,
		dungeon::MAP_HEIGHT * config::TILE_SIZE), "Dungeon Crawler");

	//	Create clock for keeping track of time in between frames.
	float deltaTime = 0.0f;
	sf::Clock clock;

	/*
	*	Set seed of random number generator for any random generation which
	*	might be necessary.
	*/
	srand(time(NULL));

	//	Create scenes and load them into SceneManager.
	testscene test;
	std::vector<Scene*> scenes = { &test };
	SceneManager manager(scenes);

	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();

		/*
		*	Clear previous data in windowEvents.
		*	Load events into config for reference by whichever class needs them.
		*	Close window on sf::Event::Closed since that should be a global
		*	response to close event.
		*/
		config::windowEvents.clear();
		sf::Event event;
	    while (window.pollEvent(event)) {
			config::windowEvents.push_back(event);
	        if (event.type == sf::Event::Closed)
	            window.close();
	    }

		/*
		*	Clear window and call Update then Draw on SceneManager. No other
		*	game related functions should occur in main.
		*/
		window.clear();
		manager.update(deltaTime);
		manager.draw(window);

		//	Display the window.
		window.display();
	}

	return 0;
}
