#include "Scene.h"

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

class SceneManager {
public:
	SceneManager(std::vector<Scene*> scenes);
	SceneManager();
	~SceneManager();

	static int ACTIVE_SCENE;

	static void setActiveScene(int id) { ACTIVE_SCENE = id; scenes[id]->Reset(); }
	void addScene(Scene* scene) { scenes.push_back(scene); }

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);

	static std::vector<Scene*> scenes;
};

#endif
