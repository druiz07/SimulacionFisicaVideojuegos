#include "ParticulasUnidasScene.h"

void ParticulasUnidasScene::initObjects() {

	GetCamera()->setEye(physx::PxVec3(0, 0, 125));
	GetCamera()->setDir(physx::PxVec3(0, 0, -1));

	forceRegistry = new ParticleForceRegistry();

	particulaA = new Particula(Vector3(40, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), { 0.3, 0.3, 0.4, 1 }, INT_MAX, 20, 5);
	particulaB = new Particula(Vector3(-40, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), { 0.6, 0, 0.2, 1 }, INT_MAX, 20, 5);

	kElasticity = new float(500.0f);

	esGoma = new bool(false);
	particleSpringA = new ParticleSpring(particulaB, kElasticity, 40, esGoma);
	gravityA = new ParticleGravity(Vector3(0, 0, 0));
	dragA = new ParticleDrag(0.1, 0);

	forceRegistry->add(particulaA, particleSpringA);
	forceRegistry->add(particulaA, gravityA);
	forceRegistry->add(particulaA, dragA);

	particleSpringB = new ParticleSpring(particulaA, kElasticity, 40, esGoma);
	gravityB = new ParticleGravity(Vector3(0, 0, 0));
	dragB = new ParticleDrag(0.1, 0);

	forceRegistry->add(particulaB, particleSpringB);
	forceRegistry->add(particulaB, gravityB);
	forceRegistry->add(particulaB, dragB);
}

void ParticulasUnidasScene::destroyObjects() {
	delete forceRegistry;
	for (auto a : generators) delete a;
	generators.clear();

	delete particulaA; delete particulaB;

	delete esGoma;
	delete kElasticity;
}

void ParticulasUnidasScene::update(float t) {
	forceRegistry->updateForces(t);
	particulaA->update(t);
	particulaB->update(t);
}

void ParticulasUnidasScene::keyPress(char k) {
	switch (k) {
	case '+': {
		(*kElasticity)++;
		std::cout << "Constante Elasticidad : " << (*kElasticity) << '\n';
		break;
	}
	case '-': {
		(*kElasticity)--;
		std::cout << "Constante Elasticidad : " << (*kElasticity) << '\n';
		break;
	}
	case 'G': {

		*esGoma = !(*esGoma);
		//if (*esGoma)std::cout << "El muelle es una goma " << "\n";
		//else std::cout << "El muelle no es una goma " << "\n";
		//break;

	}
	default:
		break;
	}
}

