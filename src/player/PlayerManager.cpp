#include "PlayerManager.h"

PlayerManager::PlayerManager(sf::RenderWindow& window, sf::View* view) : PlayerManager(window) {
		this->view = view;
}
PlayerManager::PlayerManager(sf::RenderWindow& window, sf::View* view, dungeon* map) : PlayerManager(window, view) {
	setDungeon(map);
}
PlayerManager::PlayerManager(sf::RenderWindow& window) : character(player::RANGER, player::MALE) {

}
PlayerManager::~PlayerManager() {
	delete map;
}

void PlayerManager::update(float deltaTime) {
	for(sf::Event evnt : config::windowEvents)
		if(evnt.type == sf::Event::MouseButtonPressed)
			if(evnt.mouseButton.button == sf::Mouse::Left)
				character.setPath(astar::aStar(dungeon::globalToLocal(character.getPosition()),
				dungeon::globalToLocal(config::WINDOW->mapPixelToCoords(sf::Mouse::getPosition(*config::WINDOW))),
				[this](int x, int y)->bool{ return !map->isWalkable(sf::Vector2i(x, y)); }));
	character.update(deltaTime);
	view->setCenter(character.getPosition());
}
void PlayerManager::draw(sf::RenderWindow& window) {
	character.draw(window);
}

void PlayerManager::setDungeon(dungeon* map) {
	this->map = map;
	character.setPosition(map->getStart() * (int)config::TILE_SIZE);
}
