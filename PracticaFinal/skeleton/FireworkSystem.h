#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"
#include "Firework.h"
#include <vector>
#include <list>
#include "ParticleForceRegistry.h"
#include "ParticleGravity.h"
#include "ParticleWind.h"
#include "ParticleExplosion.h"
#include "ParticleDrag.h"
#include "Explosion.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

struct typeInfo {
	Vector3 vel;
	Vector3 acc;
	Vector4 color;

	float size;
	double damp;
	float maxLifeTime;
	float minLifeTime;

	type pType;
	int numFireworksToInstantiate;

	int velMin;
	int velMax;

	type childType;

	physx::PxTransform pos = physx::PxTransform(0, 0, 0);
};

class FireworkSystem {
public:
	FireworkSystem(ParticleForceRegistry* forceRegistry, const std::vector<ParticleForceGenerator*>& generators, const std::vector<RenderItem*>& sph, 
			const std::vector<int>& sphereSizes, RenderItem* expSphere, std::list<ParticleExp>* particleExplosions);

	~FireworkSystem();

	void update(float t);
	void instantiateInitFirework();

private:
	vector<typeInfo> info;

	std::vector<RenderItem*> spheres;
	std::vector<int> sphereSizes;

	RenderItem* expSphere;

	std::vector<ParticleForceGenerator*> generators;
	ParticleForceRegistry* forceRegistry;
	list<Firework*> fireworks;

	std::list<ParticleExp>* particleExplosions;

	void instantiateFirework(type t, Vector3 parentPos = Vector3(0, 0, 0), Vector3 parentVel = Vector3(0, 0, 0));
	void explode(Firework* f);
	void createFirework(const typeInfo& type, Vector3 pos, Vector3 vel);
};


