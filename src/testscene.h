#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include <SFML/Graphics.hpp>
#include "scenes/Scene.h"
#include <functional>
#include "ui/GUIButton.h"
#include "config.h"
#include "dungeon/dungeon.h"
#include "ai/astar.h"
#include "ai/path.h"
#include <iostream>

class testscene : public Scene {
public:
	testscene();
	~testscene();

private:
	GUIButton button;
	dungeon* testDungeon;

	sf::Vector2i point1;
	sf::Vector2i point2;
	bool captured = false;

	void update(float deltaTime);

	void draw(sf::RenderWindow& window);

	void reset();
};

#endif
