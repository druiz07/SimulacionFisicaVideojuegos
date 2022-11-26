#pragma once
#include "ParticleForceGenerator.h"
#include "Particula.h"

class ParticleSpring : public ParticleForceGenerator {
public:
	ParticleSpring(Particula* _other, float* _k, float _restLength,bool* g) : other(_other), k(_k), restLength(_restLength),goma(g) {};
	virtual void updateForce(Particula* particle, float t);

private:
	Particula* other;
	float* k; //Constante de elasticidad
	bool* goma;
	float restLength; //Longitud en estado de reposo
};

