#pragma once
#include "Scene.h"
#include "ParticleAnchoredSpring.h"
#include "ParticleDrag.h"
#include "ParticleGravity.h"
#include <iostream>
using namespace std;

class MuelleAncladoScene : public Scene {

public:
	MuelleAncladoScene() {};

	void initObjects();
	void destroyObjects();
	void update(float t);
	void keyPress(char k);

private:

	ParticleForceRegistry* forceRegistry = NULL;
	std::vector<ParticleForceGenerator*> generators;

	Vector3* staticPosition = NULL;
	RenderItem* cubeRenderI = NULL;
	physx::PxTransform* cubeTr = NULL;

	Particula* particula = NULL;
	ParticleAnchoredSpring* anchoredSpring = NULL;
	ParticleGravity* gravity = NULL;
	ParticleDrag* drag = NULL;
	float* kElasticity = NULL;
};

