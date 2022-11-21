#pragma once
#include "Particula.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <vector>
#include <list>
#include "ParticleGravity.h"
#include "ParticleForceRegistry.h"
#include "ParticleDrag.h"
#include "ParticleWind.h"
#include "ParticleExplosion.h"
#include "Explosion.h"

using namespace std;

class SistemaParticulas {
public:
	SistemaParticulas(float cadence, int maxLT, int minLT, int maxV, int minV, int numP, int maxS, int minS, ParticleForceRegistry* forceRegistry, 
	const std::vector<ParticleForceGenerator*>& generators, const std::vector<RenderItem*>& sph, const std::vector<int>& sphereSizes, RenderItem* expSphere, std::list<ParticleExp>* particleExplosions);

	~SistemaParticulas();

	void update(float t);

private:
	void instantiateParticles();

	float actTime;
	float cadence;
	int maxLifeTime, minLifeTime;
	int maxSpeed, minSpeed;
	int minSize, maxSize;
	int numParticulas;

	std::vector<RenderItem*> spheres;
	std::vector<int> sphereSizes;

	RenderItem* expSphere;

	std::vector<ParticleForceGenerator*> generators;
	ParticleForceRegistry* forceRegistry;
	list<Particula*> particulas;

	std::list<ParticleExp>* particleExplosions;
};

