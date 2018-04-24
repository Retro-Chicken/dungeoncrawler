#include "EnemyManager.h"
#include <iostream>

EnemyManager::EnemyManager(sf::RenderWindow& window, sf::View* view) : EnemyManager(window) {
		this->view = view;
}
EnemyManager::EnemyManager(sf::RenderWindow& window, sf::View* view, dungeon* map) : EnemyManager(window, view) {
	setDungeon(map);
}
EnemyManager::EnemyManager(sf::RenderWindow& window) : character(enemy::RANGER) {

}
EnemyManager::~EnemyManager() {

}

void EnemyManager::update(float deltaTime) {
	character.update(deltaTime);
	character.setPath(astar::aStar(dungeon::globalToLocal(character.getPosition()),
	dungeon::globalToLocal(config::WINDOW->mapPixelToCoords(player::getPosition(*config::WINDOW))),
	[this](int x, int y)->bool{ return !map->isWalkable(sf::Vector2i(x, y)); }));
}
void EnemyManager::draw(sf::RenderWindow& window) {
	character.draw(window);
}

void EnemyManager::setDungeon(dungeon* map) {
	this->map = map;
	character.setPosition(map->spawnPoints[0] * (int)config::TILE_SIZE);
}
