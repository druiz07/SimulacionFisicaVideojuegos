#pragma once
#include "Scene.h"
#include "BodySystem.h"
#include "ParticleForceRegistry.h"
#include "BodyWind.h"
#include "BodyTorque.h"
#include "BodyExplosion.h"
using namespace physx;

class SolidosRigidosScene : public Scene {
public:
	SolidosRigidosScene(PxScene* gScene, PxPhysics* gPhysics);
	void initObjects();
	void destroyObjects();
	void update(float t);
	void keyPress(char k);

	void explosion();

private:
	PxScene* gScene;
	PxPhysics* gPhysics;

	BodySystem* bodySystem;
	RenderItem* sueloI;

	BodyWind* bodyWind;
	BodyTorque* bodyTorque;
	ParticleForceRegistry* forceRegistry;

	float inertiaOffeset=6.25;
	float sizeOffset = 3.5;
};

