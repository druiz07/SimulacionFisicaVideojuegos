#pragma once
#include "ParticleForceGenerator.h"
#include "Particula.h"
#include <iostream>

CONST Vector3 sphereExpPosition = { 0, -50, 0 };
CONST INT EXP_SPHERE_RADIUS = 50;

class ParticleExplosion : public ParticleForceGenerator
{
private:
	// Acceleration for gravity
	float f;
	RenderItem* expSphere;
	bool explota = false;

	bool pointSphere(Vector3 pointPos, const physx::PxTransform* sphereTransform) {
		return EXP_SPHERE_RADIUS > sqrt(pow(pointPos.x - sphereTransform->p.x, 2) + pow(pointPos.y - sphereTransform->p.y, 2) + pow(pointPos.z - sphereTransform->p.z, 2));
	}

public:

	ParticleExplosion(float force, RenderItem* eS) : expSphere(eS), f(force){}

	virtual void updateForce(Particula* particle, float t) {
		if (!explota) return;
		if (!particle->hasFiniteMass()) return;

		if (pointSphere(particle->getPosition(), expSphere->transform)) {
			Vector3 dir = particle->getPosition() - sphereExpPosition;
			float dist = dir.normalize();

			float force = (EXP_SPHERE_RADIUS - dist) / EXP_SPHERE_RADIUS * f;

			particle->addForce(dir * force / t);
		}

		explota = false;
	}

	void explosion(Particula* particle) {
		explota = true;
	}
};

