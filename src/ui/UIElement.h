#include <SFML\Graphics.hpp>

#ifndef UIELEMENT_H
#define UIELEMENT_H

class UIElement
{
public:
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

	virtual void RegisterEvent(sf::Event evnt) = 0;
};

#endif
