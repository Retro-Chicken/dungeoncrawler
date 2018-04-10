#include "mainscene.h"

mainscene::mainscene(sf::RenderWindow& window) : view(sf::FloatRect(0, 0, config::VIEW_WIDTH, config::VIEW_HEIGHT)),
	manager(window) {
	map = new dungeon();
	manager.setDungeon(map);
	manager.setView(&view);
}
mainscene::~mainscene() {
	delete map;
}

void mainscene::update(float deltaTime) {
	map->update(deltaTime);
	manager.update(deltaTime);
}

void mainscene::draw(sf::RenderWindow& window) {
	window.setView(view);
	map->draw(window);
	manager.draw(window);
}

void mainscene::reset() {

}
