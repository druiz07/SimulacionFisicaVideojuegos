#pragma once
#include "BodyForceGenerator.h"

class BodyWind : public BodyForceGenerator {
private:
	Vector3 w;

public:
	BodyWind(const Vector3 wind) : w(wind) {};
	void updateForce(SolidBody* body, float t) {
		body->force += w;
	}
};
