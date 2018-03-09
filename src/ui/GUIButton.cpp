#include "GUIButton.h"
//#include <Windows.h>

using namespace std;

GUIButton::GUIButton(const function<void()>& on__Click, sf::Vector2f& position, sf::Vector2f& size, sf::Color stateColors[3], sf::Text text) :
	on_Click(on__Click),
	button(size)
{
	text.setFillColor(sf::Color::Black);
	this->text = text;

	setPosition(position);
	for(int i = 0; i < 3; i++)
		this->stateColors[i] = stateColors[i];
}

GUIButton::GUIButton() {
}

GUIButton::~GUIButton() {
}

void GUIButton::Update(float deltaTime) {
}

void GUIButton::Draw(sf::RenderWindow & window) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	setState(mousePos, window);
	button.setFillColor(stateColors[currentState]);
	window.draw(button);
	window.draw(text);
}

void GUIButton::RegisterEvent(sf::Event evnt) {
	switch (evnt.type) {
	case sf::Event::MouseButtonReleased:
		if ((currentState == HIGHLIGHTED || currentState == ACTIVE) && evnt.mouseButton.button == sf::Mouse::Left) {
			onClick();
		}
		break;
	}
}

void GUIButton::setPosition(sf::Vector2f & position) {
	button.setPosition(position);
	sf::FloatRect bounds = sf::Text(text).getGlobalBounds();
	text.setPosition(position + button.getSize() / 2.0f - sf::Vector2f(bounds.width, bounds.height) / 2.0f);
}

void GUIButton::setState(sf::Vector2i & mousePos, sf::RenderWindow& window) {
	if (button.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
		currentState = HIGHLIGHTED;
	else
		currentState = UNACTIVE;
	if (currentState == HIGHLIGHTED && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		currentState = ACTIVE;
}
