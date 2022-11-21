#include "ParticleAnchoredSpring.h"

void ParticleAnchoredSpring::updateForce(Particula* particle, float t) {
	Vector3 f = particle->getPosition();
	f -= *anchor;

	float length = f.normalize();
	f *= -((length - restLenght) * (*k));
	particle->addForce(f);
}
