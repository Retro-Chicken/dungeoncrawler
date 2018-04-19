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
}
void EnemyManager::draw(sf::RenderWindow& window) {
	character.draw(window);
}

void EnemyManager::setDungeon(dungeon* map) {
	this->map = map;
	character.setPosition(map->spawnPoints[0] * (int)config::TILE_SIZE);
}
