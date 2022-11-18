#pragma once
#include "ForceGenerator.hpp"
#include "Particula.h"

class ParticleBuoyancy : public ForceGenerator {
public:
	ParticleBuoyancy(float _maxDepth, float _volume, float _waterHeight, float _liquidDensity = 1000.0f) : maxDepth(_maxDepth),
												  volume(_volume), waterHeight(_waterHeight), liquidDensity(_liquidDensity) {};

	virtual void updateForce(Particula* particle, float t);

private:
	float maxDepth;
	float volume;

	float waterHeight;
	float liquidDensity;

};

