#include "tile.h"

tile::tile(int x, int y) {
	this->x = x;
	this->y = y;
}

tile::~tile() {

}

void tile::clear() {
	for(drawable* graphic : graphics) delete graphic;
}

void tile::addDrawable(drawable* item) {
	item->setPosition(x * config::TILE_SIZE, (y + 1) * config::TILE_SIZE);
	graphics.insert(item);
}

void tile::forceDrawable(drawable* item) {
	if(graphics.find(item) != graphics.end())
		graphics.erase(item);
	addDrawable(item);
}

void tile::update(float deltaTime) {
	for(drawable* graphic : graphics)
		graphic->update(deltaTime);
}

void tile::draw(sf::RenderWindow& window) const {
	for(drawable* graphic : graphics)
		graphic->draw(window);
}
