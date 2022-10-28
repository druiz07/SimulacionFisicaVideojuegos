#pragma once
#include "Particula.hpp"
#include <list>
#include <random>

class ForceGenerator {

public:
	virtual void updateForce(Particula* p, double duration) = 0; //Metodo abtracto de actualizacion de fuerzas
	std::string _name;
	double t = -1e10;

};


