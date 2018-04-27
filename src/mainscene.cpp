#include "mainscene.h"

mainscene::mainscene(sf::RenderWindow& window) : view(sf::FloatRect(0, 0, config::VIEW_WIDTH, config::VIEW_HEIGHT)),
	manager(window), eManager(window, &manager) {
	map = new dungeon();
	manager.setDungeon(map);
	manager.setView(&view);
	eManager.setDungeon(map);

}
mainscene::~mainscene() {
	delete map;
}

void mainscene::update(float deltaTime) {
	map->update(deltaTime);
	manager.update(deltaTime);
	eManager.update(deltaTime);
}

void mainscene::draw(sf::RenderWindow& window) {
	window.setView(view);
	map->draw(window);
	manager.draw(window);
	eManager.draw(window);
}

void mainscene::reset() {

}
