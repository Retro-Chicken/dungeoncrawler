#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include <SFML/Graphics.hpp>
#include "player/PlayerManager.h"
#include "enemy/EnemyManager.h"
#include "dungeon/dungeon.h"
#include "scenes/Scene.h"

class mainscene : public Scene {
public:
	mainscene(sf::RenderWindow& window);
	~mainscene();

private:
	sf::View view;
	PlayerManager manager;
	EnemyManager eManager;
	dungeon* map;

	void update(float deltaTime);

	void draw(sf::RenderWindow& window);

	void reset();
};

#endif
