#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../dungeon/dungeon.h"
#include "../ai/astar.h"
#include "player.h"
#include "../config.h"

class PlayerManager {
public:
	PlayerManager(sf::RenderWindow& window);
	PlayerManager(sf::RenderWindow& window, sf::View* view);
	PlayerManager(sf::RenderWindow& window, sf::View* view, dungeon* map);
	~PlayerManager();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	void setView(sf::View* view) { this->view = view; }
	void setDungeon(dungeon* map);

	player* getPlayer() { return &character; }

private:
	sf::View* view;
	dungeon* map;
	player character;
};

#endif
