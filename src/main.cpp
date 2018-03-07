#include <SFML\Graphics.hpp>
#include <iostream>
#include "scenes/SceneManager.h"


int main() {
	sf::RenderWindow window(sf::VideoMode(800, 480), "Dungeon Crawler");

	float deltaTime = 0.0f;
	sf::Clock clock;

	srand(time(NULL));
	SceneManager manager;

	while (window.isOpen()) {
		sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		deltaTime = clock.restart().asSeconds();

		window.clear();
		manager.Update(deltaTime);
		manager.Draw(window);

		window.display();
	}

	return 0;
}
