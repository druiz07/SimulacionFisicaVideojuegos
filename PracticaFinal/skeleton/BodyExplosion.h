#pragma once
#include "BodyForceGenerator.h"
#include "SolidBody.h"
#include <iostream>

CONST Vector3 expPos = { 0,0,0 };

class BodyExplosion : public BodyForceGenerator
{
private:
	// Acceleration for gravity

	bool explota = false;
	Vector3 explosionDir;
	double R;
	double K;
	double constExplosion;

public:

	BodyExplosion(double RR, double kk, double cE) : R(RR), K(kk), constExplosion(cE) {}

	virtual void updateForce(SolidBody* body, float t) {
		if (!explota) return;
		double r = pow((body->rigid->getGlobalPose().p.x - expPos.x), 2) + pow((body->rigid->getGlobalPose().p.y - expPos.y), 2)
			+ pow((body->rigid->getGlobalPose().p.z - expPos.z), 2);

		r = sqrt(r);
		double e = 2.718;

		if (r < R) {

			double a = K / pow(r, 2);
			double b = pow(e, -(t / constExplosion));

			explosionDir = a * Vector3(body->rigid->getGlobalPose().p.x - expPos.x, body->rigid->getGlobalPose().p.y - expPos.y, body->rigid->getGlobalPose().p.z - expPos.z) * b;

		}




		body->rigid->addForce(explosionDir*500, PxForceMode::eACCELERATION);

		explota = false;
	}

	void explosion(SolidBody* body) {
		explota = true;
	}
};

