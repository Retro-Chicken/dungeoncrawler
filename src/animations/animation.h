#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class animation {
public:
	animation(sf::Texture* texture, sf::IntRect textureRect, int columns, int count, float animTime);
	~animation();

	void draw(sf::RenderWindow& update);
	void update(float deltaTime);

private:

};

#endif
