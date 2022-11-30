#pragma once
#include "ParticleForceGenerator.h"
#include "Particula.h"

class ParticleBuoyancy : public ParticleForceGenerator {
public:
	ParticleBuoyancy(float _waterHeight, float _liquidDensity = 13600.0f) :
		waterHeight(_waterHeight), liquidDensity(_liquidDensity) {};

	virtual void updateForce(Particula* particle, float t);

private:


	float waterHeight;
	float liquidDensity;

};

