#pragma once
#include "ParticleForceGenerator.h"
#include "Particula.h"

class ParticleDrag : public ParticleForceGenerator {
private:
	// Coefficient for velocity
	float k1;
	// Coefficient for squared velocity
	float k2;
public:
	ParticleDrag(float _k1, float _k2) : k1(_k1), k2(_k2) {}

	virtual void updateForce(Particula* particle, float t) {
		Vector3 f = particle->getVel();

		// Drag coeffient
		float dragCoeff = f.normalize();
		dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

		// Final force
		f *= -dragCoeff;
		particle->addForce(f);
	}

};

