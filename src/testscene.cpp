#include "testscene.h"
#include "config.h"
#include <iostream>

static sf::Color buttonColor[] = { sf::Color(100, 10, 10), sf::Color(75, 10, 10), sf::Color(50, 10, 10) };

testscene::testscene() {
	sf::Text buttonText = sf::Text("Test Button", config::MAIN_FONT, 60);
	buttonText.setScale(sf::Vector2f(0.5, 0.5));
	sf::Vector2f position(150, 100);
	sf::Vector2f size(500, 200);
	button = GUIButton([]() { cout << "Button Clicked." << endl; }, position, size, buttonColor, buttonText);
}

testscene::~testscene() {

}

void testscene::update(float deltaTime) {
	for(int i = 0; i < config::windowEvents.size(); i++)
		button.registerEvent(config::windowEvents[i]);
	button.update(deltaTime);
}

void testscene::draw(sf::RenderWindow& window) {
	button.draw(window);
}

void testscene::reset() {

}
