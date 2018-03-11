#include "testscene.h"

static sf::Color buttonColor[] = { sf::Color(100, 10, 10), sf::Color(75, 10, 10), sf::Color(50, 10, 10) };

testscene::testscene() {
	sf::Text buttonText = sf::Text("New Dungeon", config::MAIN_FONT, 60);
	buttonText.setScale(sf::Vector2f(0.5, 0.5));
	sf::Vector2f position(600, 200);
	sf::Vector2f size(200, 100);
	button = GUIButton([this]() { testDungeon = dungeon(); }, position, size, buttonColor, buttonText);
}

testscene::~testscene() {

}

void testscene::update(float deltaTime) {
	for(int i = 0; i < config::windowEvents.size(); i++)
		button.registerEvent(config::windowEvents[i]);
	button.update(deltaTime);
}

void testscene::draw(sf::RenderWindow& window) {
	window.clear();
	testDungeon.draw(window);
	button.draw(window);
}

void testscene::reset() {

}
