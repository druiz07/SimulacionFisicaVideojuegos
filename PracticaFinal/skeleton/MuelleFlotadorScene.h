#pragma once
#include "Scene.h"
#include "ParticleBuoyancy.h"
#include "ParticleDrag.h"
#include "ParticleGravity.h"

class MuelleFlotadorScene : public Scene {
public:
	MuelleFlotadorScene() {};

	void initObjects();
	void destroyObjects();
	void update(float t);

private:
	ParticleForceRegistry* forceRegistry = NULL;
	std::vector<ParticleForceGenerator*> generators;

	RenderItem* mar = NULL;
	physx::PxTransform* marTr = NULL;
	Particula* pFlotante = NULL;
	ParticleBuoyancy* buoyancy = NULL;
	ParticleGravity* gravity = NULL;
	ParticleDrag* drag = NULL;
};

