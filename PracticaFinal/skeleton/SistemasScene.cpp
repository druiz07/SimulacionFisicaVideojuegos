#include "SistemasScene.h"

void SistemasScene::initObjects() {

	GetCamera()->setEye(physx::PxVec3(0, -100, 400));
	GetCamera()->setDir(physx::PxVec3(0, 0, -1));

	//Lista de explosiones
	particleExplosions = new std::list<ParticleExp>();

	//Esferas viento
	spheres.push_back(new RenderItem(CreateShape(physx::PxSphereGeometry(sphereSizes[RIGHTDIRWIND])), sphereAPos, Vector4(1, 0, 0, 0)));
	spheres.push_back(new RenderItem(CreateShape(physx::PxSphereGeometry(sphereSizes[LEFTDIRWIND])), sphereBPos, Vector4(1, 0, 0, 0)));
	spheres.push_back(new RenderItem(CreateShape(physx::PxSphereGeometry(sphereSizes[RANDOMDIRWIND])), sphereCPos, Vector4(1, 0, 0, 0)));

	//Esfera de explosion
	expSphere = new RenderItem(CreateShape(physx::PxSphereGeometry(50)), expSpherePos, Vector4(0, 1, 0, 0));

	//Registro de las fuerzas de las particulas
	forceRegistry = new ParticleForceRegistry();

	fireworkSystem = new FireworkSystem(forceRegistry, generators, spheres, sphereSizes, expSphere, particleExplosions);
	pSystem = new SistemaParticulas(0.5, 10, 5, 2, 4, 10, 15, 10, forceRegistry, generators, spheres, sphereSizes, expSphere, particleExplosions);

	explosion = new Explosion(particleExplosions);
}

void SistemasScene::update(float t) {
	forceRegistry->updateForces(t);
	pSystem->update(t);
	fireworkSystem->update(t);
}

void SistemasScene::keyPress(char k) {
	switch (k)
	{
		case 'F': {
			fireworkSystem->instantiateInitFirework();
			break;
		}
		case 'E': {
				explosion->explode();
				break;
		}
		default:
			break;
	}
}

void SistemasScene::destroyObjects() {
	//Sistemas y generador
	delete forceRegistry;
	delete fireworkSystem;
	delete pSystem;

	for (auto a : generators) delete a;
	generators.clear();

	//Lista de explosiones
	delete particleExplosions;
	delete explosion;

	//Esferas de viento y explosion
	delete sphereAPos;
	delete sphereBPos;
	delete sphereCPos;
	delete expSpherePos;

	for (auto a : spheres) {
		DeregisterRenderItem(a);
		delete a;
	}
	DeregisterRenderItem(expSphere);
	delete expSphere;
}
