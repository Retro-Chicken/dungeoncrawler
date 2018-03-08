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

	void Update(float deltaTime);

	void Draw(sf::RenderWindow& window);

	void Reset();
};

#endif
