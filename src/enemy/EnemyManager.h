#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../dungeon/dungeon.h"
#include "enemy.h"
#include "../config.h"
#include "../player/player.h"
#include "../player/PlayerManager.h"
#include "../ai/astar.h"
#include "../ai/path.h"

class EnemyManager {
public:
	EnemyManager(sf::RenderWindow& window, PlayerManager* pManager);
	EnemyManager(sf::RenderWindow& window, sf::View* view, PlayerManager* pManager);
	EnemyManager(sf::RenderWindow& window, sf::View* view, dungeon* map, PlayerManager* pManager);
	~EnemyManager();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	void setView(sf::View* view) { this->view = view; }
	void setDungeon(dungeon* map);

private:
	sf::View* view;
	dungeon* map;
	std::vector<enemy*> enemies;
	PlayerManager* pManager;
};

#endif
