#pragma once
#include "Particula.h"
#include <list>
#include <random>

class ForceGenerator {

public:
	virtual void updateForce(Particula* particle, float t) {};
	std::string _name;
	double t = -1e10;

};


