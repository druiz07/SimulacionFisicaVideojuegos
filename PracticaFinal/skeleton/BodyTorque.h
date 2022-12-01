#pragma once
#include "BodyForceGenerator.h"

class BodyTorque : public BodyForceGenerator {
private:
	Vector3 torque;

public:
	BodyTorque(const Vector3 t) : torque(t) {};
	void updateForce(SolidBody* body, float t) {
		body->torque += torque;
	}
};
