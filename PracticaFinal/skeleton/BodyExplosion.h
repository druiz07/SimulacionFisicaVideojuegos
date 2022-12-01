#pragma once
#include "BodyForceGenerator.h"
#include "SolidBody.h"
#include <iostream>

CONST Vector3 expPos = { 0,0,0 };

class BodyExplosion : public BodyForceGenerator
{
private:
	// Acceleration for gravity
	float f;
	bool explota = false;
public:

	BodyExplosion(float force) : f(force) {}

	virtual void updateForce(SolidBody* body, float t) {
		if (!explota) return;

		Vector3 dir = body->rigid->getGlobalPose().p - expPos;
		float dist = dir.normalize();

		body->rigid->addForce(dir * f / t, PxForceMode::eACCELERATION);

		explota = false;
	}

	void explosion(SolidBody* body) {
		explota = true;
	}
};

