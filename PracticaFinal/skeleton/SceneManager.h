#pragma once
#include "Scene.h"
#include <iostream>
using namespace std;

class SceneManager {
public:
	SceneManager() {};
	SceneManager(Scene* scene, SceneNames name); 
	~SceneManager();

	void loadScene(Scene* scene, SceneNames name);
	void removeScene();
	Scene* getCurrentScene();

private:
	Scene* scene;
};

