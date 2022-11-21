#pragma once
#include "Particula.h"

class ParticleForceGenerator
{
public:
	// Overload to provide functionality
	virtual void updateForce(Particula* particula, float t) = 0;
};