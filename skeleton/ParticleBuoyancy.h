#pragma once
#include "ForceGenerator.hpp"
#include "ParticulaBote.h"

class ParticleBuoyancy : public ForceGenerator {
public:
	ParticleBuoyancy(float _waterHeight, float _liquidDensity = 1000.0f) :
		waterHeight(_waterHeight), liquidDensity(_liquidDensity) {};

	virtual void updateForce(Particula* p, float t);

private:

	float waterHeight;
	float liquidDensity;

};

