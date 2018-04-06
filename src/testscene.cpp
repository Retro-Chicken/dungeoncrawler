#include "testscene.h"

static sf::Color buttonColor[] = { sf::Color(100, 10, 10), sf::Color(75, 10, 10), sf::Color(50, 10, 10) };

testscene::testscene() : character(player::RANGER, player::MALE) {
	testDungeon = new dungeon();
	sf::Text buttonText = sf::Text("New Dungeon", config::MAIN_FONT, 60);
	buttonText.setScale(sf::Vector2f(0.5, 0.5));
	sf::Vector2f position(500, 650);
	sf::Vector2f size(200, 100);
	button = GUIButton([this]() { delete testDungeon; testDungeon = new dungeon(); },
	position, size, buttonColor, buttonText);
}

testscene::~testscene() {
	delete testDungeon;
}

void testscene::update(float deltaTime) {
	for(int i = 0; i < config::windowEvents.size(); i++)
		button.registerEvent(config::windowEvents[i]);
	button.update(deltaTime);
	testDungeon->update(deltaTime);
	character.update(deltaTime);

	for(sf::Event evnt : config::windowEvents)
		if(evnt.type == sf::Event::MouseButtonPressed) {
			if(evnt.mouseButton.button == sf::Mouse::Left) {
				if(!captured) {
					point1 = dungeon::globalToLocal(sf::Mouse::getPosition(*config::WINDOW));
					character.setPosition(point1);
					captured = true;
				} else {
					point2 = dungeon::globalToLocal(sf::Mouse::getPosition(*config::WINDOW));
					character.setPath(astar::aStar(point1, point2,
					[this](int x, int y)->bool{ return !testDungeon->isWalkable(sf::Vector2i(x, y)); }));
					captured = false;
				}
			}
		}
}

void testscene::draw(sf::RenderWindow& window) {
	window.clear();
	testDungeon->draw(window);
	character.draw(window);
	button.draw(window);
}

void testscene::reset() {

}
