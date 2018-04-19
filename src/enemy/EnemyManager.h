#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../dungeon/dungeon.h"
#include "../ai/astar.h"
#include "enemy.h"
#include "../config.h"

class EnemyManager {
public:
	EnemyManager(sf::RenderWindow& window);
	EnemyManager(sf::RenderWindow& window, sf::View* view);
	EnemyManager(sf::RenderWindow& window, sf::View* view, dungeon* map);
	~EnemyManager();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	void setView(sf::View* view) { this->view = view; }
	void setDungeon(dungeon* map);

private:
	sf::View* view;
	dungeon* map;
	enemy character;
};

#endif
