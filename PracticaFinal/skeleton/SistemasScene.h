#pragma once
#include "Scene.h"
#include "SistemaParticulas.h"
#include "FireworkSystem.h"

//Escena con el sistema de particulas y el sistema de fuegos artificiales

class SistemasScene : public Scene {

public:
	SistemasScene() {};
	void initObjects();
	void destroyObjects();
	void update(float t);
	void keyPress(char k);

private:
	ParticleForceRegistry* forceRegistry = NULL;
	std::vector<ParticleForceGenerator*> generators;

	FireworkSystem* fireworkSystem = NULL;
	SistemaParticulas* pSystem = NULL;

	//Esferas de viento
	std::vector<RenderItem*> spheres;
	physx::PxTransform* sphereAPos = new physx::PxTransform(0, 100, 0);
	physx::PxTransform* sphereBPos = new physx::PxTransform(0, -200, 0);
	physx::PxTransform* sphereCPos = new physx::PxTransform(-120, -350, 0);
	std::vector<int> sphereSizes = { 50, 50, 100 };

	//Esfera de explosion
	physx::PxTransform* expSpherePos = new physx::PxTransform(0, -50, 0);
	RenderItem* expSphere = NULL;

	//Lista de fuerzas de explosion
	std::list<ParticleExp>* particleExplosions = NULL;

	Explosion* explosion = NULL;
};

