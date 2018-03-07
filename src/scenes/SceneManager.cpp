#include "SceneManager.h"


int SceneManager::ACTIVE_SCENE = -1;
std::vector<Scene*> SceneManager::scenes;

SceneManager::SceneManager(std::vector<Scene*> scenes) {
	this->scenes = scenes;
	ACTIVE_SCENE = 0;
}

SceneManager::SceneManager() {
	ACTIVE_SCENE = -1;
}

SceneManager::~SceneManager() {
}

void SceneManager::Draw(sf::RenderWindow & window) {
	if(ACTIVE_SCENE >= 0)
		scenes[ACTIVE_SCENE]->Draw(window);
}

void SceneManager::Update(float deltaTime) {
	if(ACTIVE_SCENE >= 0)
		scenes[ACTIVE_SCENE]->Update(deltaTime);
}
