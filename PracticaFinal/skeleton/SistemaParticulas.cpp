#include "SistemaParticulas.h"
#include <iostream>

SistemaParticulas::SistemaParticulas(float c, int maxLT, int minLT, int maxV, int minV, int nP, int maxS, int minS, ParticleForceRegistry* fR,
	const std::vector<ParticleForceGenerator*>& gen, const std::vector<RenderItem*>& sph, const std::vector<int>& sSizes, RenderItem* eS, std::list<ParticleExp>* pExps) {
	cadence = c;

	forceRegistry = fR;

	sphereSizes = sSizes;
	spheres = sph;

	maxLifeTime = maxLT; minLifeTime = minLT;
	maxSpeed = maxV; minSpeed = minV;
	maxSize = maxS; minSize = minS;

	numParticulas = nP;

	actTime = 0;

	generators = gen;

	expSphere = eS;

	particleExplosions = pExps;

	srand(time(NULL));
}

SistemaParticulas::~SistemaParticulas() {
	for (auto a : particulas) delete a;
}

void SistemaParticulas::generateParticles() {
	float ang = 0;
	for (int i = 0; i < numParticulas; i++) {
		float x = cos(ang);
		float z = sin(ang);

		float v = rand() % minSpeed + maxSpeed; //Random de la velocidad
		float l = rand() % minLifeTime + maxLifeTime; //Random de lifeTime

		float r = (rand() % 9 + 1); r /= 10;
		float g = (rand() % 9 + 1); g /= 10;
		float b = (rand() % 9 + 1); b /= 10;

		float s = rand() % maxSize + minSize;

		auto p = new Particula(Vector3(0, 0, 0), Vector3(v * x, 0, v * z), Vector3(0, 0, 0), { r, g, b, 1 }, l, s, 5);

		ParticleGravity* gravity = new ParticleGravity(Vector3(0, -9.8, 0));
		ParticleWind* wind = new ParticleWind(Vector3(30, 0, 0), spheres, sphereSizes);
		ParticleExplosion* explosion = new ParticleExplosion(500, expSphere);
		ParticleDrag* drag = new ParticleDrag(0, 0);

		generators.push_back(gravity); generators.push_back(wind); generators.push_back(explosion); generators.push_back(drag);

		particleExplosions->push_back({ explosion, p });
		
		forceRegistry->add(p, wind);
		forceRegistry->add(p, gravity);
		forceRegistry->add(p, explosion);
		forceRegistry->add(p, drag);

		particulas.push_back(p);

		ang += (360/numParticulas);
	}
}

void SistemaParticulas::update(float t) {

	auto p = particulas.begin();
	while (p != particulas.end()) {

		if ((*p)->alive()) {
			(*p)->update(t);
			p++;
		}
		else {
			forceRegistry->deleteParticleRegistry(*p);
			delete *p;
			p = particulas.erase(p);
		}
	}

	actTime -= t;
	if (actTime < 0) {
		generateParticles();
		actTime = cadence;
	}
}

