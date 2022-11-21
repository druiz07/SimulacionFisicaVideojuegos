#pragma once
#include "Scene.h"
#include "ParticleDrag.h"
#include "ParticleGravity.h"
#include "ParticleSpring.h"
#include <iostream>
using namespace std;

class ParticulasUnidasScene : public Scene {
public:
	ParticulasUnidasScene() {};

	void initObjects();
	void destroyObjects();
	void update(float t);
	void keyPress(char k);

private:
	ParticleForceRegistry* forceRegistry = NULL;
	std::vector<ParticleForceGenerator*> generators;

	float* kElasticity = NULL;

	Particula* particulaA = NULL;
	ParticleSpring* particleSpringA = NULL;
	ParticleGravity* gravityA = NULL;
	ParticleDrag* dragA = NULL;

	Particula* particulaB = NULL;
	ParticleSpring* particleSpringB = NULL;
	ParticleGravity* gravityB = NULL;
	ParticleDrag* dragB = NULL;
};

