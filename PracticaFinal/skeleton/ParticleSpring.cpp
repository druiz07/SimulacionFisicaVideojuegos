#include "ParticleSpring.h"

void ParticleSpring::updateForce(Particula* particle, float t) {
	Vector3 f = particle->getPosition();
	f -= other->getPosition();

	//Longitud
	float length = f.normalize();

	float deltaL = length - restLength;

	float forceMagnitude = -(*k) * deltaL;
	f *= forceMagnitude;

	particle->addForce(f);
}
