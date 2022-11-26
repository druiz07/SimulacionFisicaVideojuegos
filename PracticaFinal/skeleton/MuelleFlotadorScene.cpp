#include "MuelleFlotadorScene.h"

void MuelleFlotadorScene::initObjects() {

	GetCamera()->setEye(physx::PxVec3(0, 10, 100));
	GetCamera()->setDir(physx::PxVec3(0, 0, -1));

	forceRegistry = new ParticleForceRegistry();

	marTr = new physx::PxTransform(Vector3(0,0,0));

	mar = new RenderItem(CreateShape(physx::PxBoxGeometry(20.0, 0.1, 20.0)), marTr, { 0.3, 0.3, 0.4, 1 });

	pFlotante = new Particula(Vector3(0, 30, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), { 0.6, 0, 0.2, 1 }, INT_MAX, 20, 5);
	pFlotante->setdepthVol(0.3, 0.1);
	buoyancy = new ParticleBuoyancy( 0);
	gravity = new ParticleGravity(Vector3(0, -9.8, 0));
	drag = new ParticleDrag(10, 0);

	forceRegistry->add(pFlotante, gravity);
	forceRegistry->add(pFlotante, drag);
	forceRegistry->add(pFlotante, buoyancy);
}

void MuelleFlotadorScene::destroyObjects() {
	delete pFlotante; DeregisterRenderItem(mar); delete mar;
	delete marTr; delete buoyancy;
	delete drag; delete gravity;
}

void MuelleFlotadorScene::update(float t) {
	forceRegistry->updateForces(t);
	pFlotante->update(t);
}

