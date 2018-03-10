#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include "../config.h"

#ifndef SCENE_H
#define SCENE_H

using namespace std;

class Scene {
public:
	Scene();
	~Scene();

	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void reset() = 0;

protected:
	void resizeView(const sf::RenderWindow& window, sf::View& view);
	sf::Vector2u oldWindowSize;
};

#endif
