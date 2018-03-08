#include "testscene.h"

static sf::Color buttonColor[] = { sf::Color(100, 10, 10), sf::Color(75, 10, 10), sf::Color(50, 10, 10) };

void buttonFunc();

testscene::testscene() {
	sf::Text buttonText = sf::Text("Test Button", config::MAIN_FONT, 60);
	buttonText.setScale(sf::Vector2f(0.05, 0.05));
	button = GUIButton(&buttonFunc, sf::Vector2f(320 - 50 - 5, 192 - 20 - 5), sf::Vector2f(50, 20), buttonColor, buttonText);
}

void buttonFunc() {

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
