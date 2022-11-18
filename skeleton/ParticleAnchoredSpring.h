#pragma once
#include "ForceGenerator.hpp"
class ParticleAnchoredSpring : public ForceGenerator {
public:
	ParticleAnchoredSpring(Vector3* _anchor, float* _k, float _restLenght) : anchor(_anchor), k(_k), restLenght(_restLenght) {};
	virtual void updateForce(Particula* particle, float t);
private:
	Vector3* anchor;

	//Constante de elasticidad
	float* k; 

	//Longitud en estado de reposo
	float restLenght;
};

