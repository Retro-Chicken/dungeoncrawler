#include <SFML\Graphics.hpp>
#include <iostream>
#include "scenes/SceneManager.h"
#include "testscene.h"
#include "config.h"


int main() {
	config::MAIN_FONT.loadFromFile("resources/fonts/arial.ttf");

	sf::RenderWindow window(sf::VideoMode(800, 480), "Dungeon Crawler");

	float deltaTime = 0.0f;
	sf::Clock clock;

	srand(time(NULL));
	testscene test;
	std::vector<Scene*> scenes = { &test };
	SceneManager manager(scenes);

	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();

		window.clear();
		manager.Update(deltaTime);
		manager.Draw(window);

		window.display();
	}

	return 0;
}
