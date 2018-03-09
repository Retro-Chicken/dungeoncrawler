#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <SFML/Graphics.hpp>

class UIElement
{
public:
	UIElement();
	~UIElement();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

	virtual void RegisterEvent(sf::Event evnt) = 0;
};

#endif
