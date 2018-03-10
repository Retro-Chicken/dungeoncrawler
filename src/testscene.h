#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "scenes/Scene.h"
#include <functional>
#include "ui/GUIButton.h"

class testscene : public Scene {
public:
	testscene();
	~testscene();

private:
	GUIButton button;

	void update(float deltaTime);

	void draw(sf::RenderWindow& window);

	void reset();
};

#endif
