#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <SFML/Graphics.hpp>

class UIElement
{
public:
	UIElement();
	~UIElement();

	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	virtual void registerEvent(sf::Event evnt) = 0;
};

#endif
