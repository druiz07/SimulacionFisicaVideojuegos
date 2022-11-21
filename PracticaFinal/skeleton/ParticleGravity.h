#pragma once
#include "ParticleForceGenerator.h"
#include "Particula.h"

class ParticleGravity : public ParticleForceGenerator
{
	// Acceleration for gravity
	Vector3 g;
public:
	ParticleGravity(const Vector3& gravity) : g(gravity) {}
	virtual void updateForce(Particula* particle, float t) {
		if (!particle->hasFiniteMass()) return;
		particle->addForce(g * particle->getMass());
	}
};
