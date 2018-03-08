#include "testscene.h"
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

void testscene::Update(float deltaTime) {
	button.Update(deltaTime);
}

void testscene::Draw(sf::RenderWindow& window) {
	sf::Event event;
    while (window.pollEvent(event)) {
		button.RegisterEvent(event);
        if (event.type == sf::Event::Closed)
            window.close();
    }
	button.Draw(window);
}

void testscene::Reset() {

}
