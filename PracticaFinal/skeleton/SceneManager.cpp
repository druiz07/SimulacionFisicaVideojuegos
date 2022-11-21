#include "SceneManager.h"

SceneManager::SceneManager(Scene* s, SceneNames n) {
	scene = s;
	scene->initObjects();
}

SceneManager::~SceneManager() {
	removeScene();
}

void SceneManager::loadScene(Scene* s, SceneNames n) {
	if (scene != nullptr) removeScene();

	scene = s;
	scene->initObjects();
}

void SceneManager::removeScene() {
	scene->destroyObjects();
	delete scene;
}

Scene* SceneManager::getCurrentScene() {
	return scene;
}
