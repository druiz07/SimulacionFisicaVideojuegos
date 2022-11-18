#pragma once
#include "ForceGenerator.hpp"
#include "Particula.h"

class ParticleSpring : public ForceGenerator {
public:
	ParticleSpring(Particula* _other, float* _k, float _restLength) : other(_other), k(_k), restLength(_restLength) {};
	virtual void updateForce(Particula* particle, float t);

private:
	Particula* other;
	float* k; //Constante de elasticidad

	float restLength; //Longitud en estado de reposo
};

