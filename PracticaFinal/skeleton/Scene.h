#pragma once
#include "ParticleForceGenerator.h"
#include "ParticleForceRegistry.h"

enum class SceneNames { SISTEMAS, MUELLE_ANCLADO, PARTICULAS_UNIDAS, MUELLE_FLOTADOR, SOLIDOS_RIGIDOS };

class Scene {
public:
	Scene() {};

	virtual void initObjects() {};
	virtual void destroyObjects() {};
	virtual void update(float t) {};
	virtual void keyPress(char k) {};
};

