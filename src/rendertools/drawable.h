#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "anchor.h"
#include <SFML/Graphics.hpp>

class drawable {
public:
	std::string tag;
	int layer = 0;
	int x = 0;
	int y = 0;

	bool operator< (const drawable& obj) const {
		return this->layer < obj.layer;
	}

	sf::IntRect getTextureRect() { return textureRect; }

	void setAnchor(anchor::ANCHOR origin) { this->origin = origin; }

	drawable(int x, int y, sf::Texture* texture, sf::IntRect textureRect);
	drawable(int x, int y, sf::Texture* texture, sf::IntRect textureRect, int layer);
	drawable(sf::Texture* texture, sf::IntRect textureRect);
	drawable(sf::Texture* texture, sf::IntRect textureRect, int layer);

	void setPosition(int x, int y);

	void draw(sf::RenderWindow& window) const;
	void draw(sf::RenderWindow& window, bool flipped);
	void draw(int x, int y, sf::RenderWindow& window);

	virtual void update(float deltaTime) {}
protected:
	anchor::ANCHOR origin = anchor::ANCHOR_BOTTOM_LEFT;
	sf::Texture* texture;
	sf::Sprite sprite;
	sf::IntRect textureRect;
};

#endif
