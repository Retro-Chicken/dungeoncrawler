#include "EnemyManager.h"
#include <iostream>

EnemyManager::EnemyManager(sf::RenderWindow& window, sf::View* view, PlayerManager* pManager) : EnemyManager(window, pManager) {
		this->view = view;
}
EnemyManager::EnemyManager(sf::RenderWindow& window, sf::View* view, dungeon* map, PlayerManager* pManager) : EnemyManager(window, view, pManager) {
	setDungeon(map);
}
EnemyManager::EnemyManager(sf::RenderWindow& window, PlayerManager* pManager) {
	this->pManager = pManager;
}
EnemyManager::~EnemyManager() {
	enemies.erase(enemies.begin(), enemies.end());
}

void EnemyManager::update(float deltaTime) {
	for(enemy* enem : enemies) {
		path newPath = astar::aStar(dungeon::globalToLocal(enem->getPosition()),
		dungeon::globalToLocal(enem->getTarget()->getPosition()),
		[this](int x, int y)->bool{
			bool result = true;
			for(enemy* enem : enemies)
				if(x == dungeon::globalToLocal(enem->getPosition()).x && y == dungeon::globalToLocal(enem->getPosition()).y)
					result = false;
			return !result || !map->isWalkable(sf::Vector2i(x, y));
		});
		if(newPath.points.size() <= 10)
			enem->setPath(newPath);
		enem->update(deltaTime);
	}
}
void EnemyManager::draw(sf::RenderWindow& window) {
	for(enemy* enem : enemies)
		enem->draw(window);
}

void EnemyManager::setDungeon(dungeon* map) {
	this->map = map;
	for(const sf::Vector2i& vec : map->spawnPoints) {
		enemy* temp = new enemy(enemy::ORC, enemy::TWO, pManager->getPlayer());
		temp->setPosition(vec * (int)config::TILE_SIZE);
		enemies.push_back(temp);
	}
}
