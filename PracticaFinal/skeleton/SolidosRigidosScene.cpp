#include "SolidosRigidosScene.h"

SolidosRigidosScene::SolidosRigidosScene(PxScene* scene, PxPhysics* physics) {
	gScene = scene;
	gPhysics = physics;
}

void SolidosRigidosScene::initObjects() {
	GetCamera()->setEye(physx::PxVec3(0, 70, 260));
	GetCamera()->setDir(physx::PxVec3(0, 0, -1));

	//Suelo
	PxShape* shape = CreateShape(PxBoxGeometry(100, 1, 100));
	PxRigidStatic* ground = gPhysics->createRigidStatic({ 0,0,0 });
	
	ground->attachShape(*shape);
	gScene->addActor(*ground);
	sueloI = new RenderItem(shape, ground, { 0.56, 0.5, 0.3, 1 });

	forceRegistry = new ParticleForceRegistry();

	bodySystem = new BodySystem(gScene, gPhysics, forceRegistry, { 0, 50, 0 });

	bodyWind = new BodyWind(Vector3(100, 0, 0));
	bodyTorque = new BodyTorque(Vector3(0, 200, 0));
}

void SolidosRigidosScene::destroyObjects() {
	delete bodySystem;

	DeregisterRenderItem(sueloI);
	delete sueloI;

	forceRegistry->clearBodyForces();
	delete forceRegistry;
}

void SolidosRigidosScene::update(float t) {
	if (bodySystem) {
		forceRegistry->addBodyForce(bodySystem->getBodies(), bodyWind);
		forceRegistry->addBodyForce(bodySystem->getBodies(), bodyTorque);
		forceRegistry->addBodyExplosionForce(bodySystem->getBodies(), 200);

		forceRegistry->updateBodyForces(t);
		bodySystem->update(t);
	}
}

void SolidosRigidosScene::keyPress(char k) {
	switch (k)
	{
		case 'E': {
			explosion();
			break;
		}
		default:
			break;
	}
}

void SolidosRigidosScene::explosion() {
	auto bodies = bodySystem->getBodies();
	for (auto b : bodies) {
		b->bodyExplosionForce->explosion(b);
	}
}
