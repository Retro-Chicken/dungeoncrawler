#include "drawable.h"

drawable::drawable(int x, int y, sf::Texture* texture, sf::IntRect textureRect) {
	this->x = x;
	this->y = y;
	sprite.setPosition(x * config::TILE_SIZE, (y + 1) * config::TILE_SIZE);
	anchor::anchorSprite(sprite, origin);
	this->texture = texture;
	sprite.setTexture(*texture);
	sprite.setTextureRect(textureRect);
}
drawable::drawable(int x, int y, sf::Texture* texture, sf::IntRect textureRect, int layer) : drawable(x, y, texture, textureRect) {
	this->layer = layer;
}
drawable::drawable(sf::Texture* texture, sf::IntRect textureRect) {
	this->texture = texture;
	sprite.setTexture(*texture);
	sprite.setTextureRect(textureRect);
}
drawable::drawable(sf::Texture* texture, sf::IntRect textureRect, int layer) : drawable(texture, textureRect) {
	this->layer = layer;
}

void drawable::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
	sprite.setPosition(x, y);
	anchor::anchorSprite(sprite, origin);
}

void drawable::draw(sf::RenderWindow& window) const {
	window.draw(sprite);
}

void drawable::draw(int x, int y, sf::RenderWindow& window) {
	sprite.setPosition(x, y);
	anchor::anchorSprite(sprite, origin);
	window.draw(sprite);
	sprite.setPosition(this->x * config::TILE_SIZE, (this->y + 1) * config::TILE_SIZE);
	anchor::anchorSprite(sprite, origin);
}
