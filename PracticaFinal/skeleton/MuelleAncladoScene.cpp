#include "MuelleAncladoScene.h"

void MuelleAncladoScene::initObjects() {

	GetCamera()->setEye(physx::PxVec3(0, -50, 150));
	GetCamera()->setDir(physx::PxVec3(0, 0, -1));

   //Registro de las fuerzas de las particulas
	forceRegistry = new ParticleForceRegistry();

	staticPosition = new Vector3(0, 0, 0);
	cubeTr = new physx::PxTransform(*staticPosition);

	cubeRenderI = new RenderItem(CreateShape(physx::PxBoxGeometry(4.0, 4.0, 4.0)), cubeTr, { 0.3, 0.3, 0.4, 1 });

	particula = new Particula(Vector3(0, -50, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), { 0.6, 0, 0.2, 1 }, INT_MAX, 20, 25);

	kElasticity = new float(5.0f);

	anchoredSpring = new ParticleAnchoredSpring(staticPosition, kElasticity, 40);
	gravity = new ParticleGravity(Vector3(0, -9.8, 0));
	drag = new ParticleDrag(0.1, 0);

	forceRegistry->add(particula, anchoredSpring);
	forceRegistry->add(particula, gravity);
	forceRegistry->add(particula, drag);
}

void MuelleAncladoScene::destroyObjects() {
	delete forceRegistry;
	for (auto a : generators) delete a;
	generators.clear();

	delete staticPosition; DeregisterRenderItem(cubeRenderI); delete cubeRenderI;
	delete cubeTr;         delete particula;
	delete anchoredSpring; delete gravity;
	delete drag;	

	delete kElasticity;
}

void MuelleAncladoScene::update(float t) {
	forceRegistry->updateForces(t);
	particula->update(t);
}

void MuelleAncladoScene::keyPress(char k) {
	switch (k) {
		case '+': {
			(*kElasticity)++;
			std::cout << "Constante Elasticidad : " <<  (*kElasticity) << '\n';
			break;
		}
		case '-': {
			(*kElasticity)--;
			std::cout << "Constante Elasticidad : " << (*kElasticity) << '\n';
			break;
		}
		default:
			break;
	}
}
