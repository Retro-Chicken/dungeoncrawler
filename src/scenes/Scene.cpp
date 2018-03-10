#include "Scene.h"

Scene::Scene() {
}


Scene::~Scene() {
}

void Scene::resizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(config::VIEW_HEIGHT * aspectRatio, config::VIEW_HEIGHT);
}
