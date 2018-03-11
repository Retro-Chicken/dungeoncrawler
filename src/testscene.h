#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "scenes/Scene.h"
#include <functional>
#include "ui/GUIButton.h"
#include "config.h"
#include "dungeon/dungeon.h"
#include <iostream>

class testscene : public Scene {
public:
	testscene();
	~testscene();

private:
	GUIButton button;
	dungeon testDungeon;

	void update(float deltaTime);

	void draw(sf::RenderWindow& window);

	void reset();
};

#endif
