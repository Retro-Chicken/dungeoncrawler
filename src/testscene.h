#include "scenes/Scene.h"
#include <functional>
#include "ui/GUIButton.h"

class testscene : public Scene {
public:
	testscene();
	~testscene();

private:
	GUIButton button;
	//void buttonFunc();

	void Update(float deltaTime);

	void Draw(sf::RenderWindow& window);

	void Reset();
};
