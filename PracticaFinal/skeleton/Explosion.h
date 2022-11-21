#pragma once
#include <list>
#include "ParticleExplosion.h"

struct ParticleExp {
	ParticleExplosion* exp;
	Particula* p;
};

class Explosion {
public:
	Explosion(std::list<ParticleExp>* pExps) : particleExplosions(pExps){}

	void explode() {
		for (auto a : *particleExplosions) {
			a.exp->explosion(a.p);
		}
	}
private:
	std::list<ParticleExp>* particleExplosions;
};
