#include "FireworkSystem.h"
#include <iostream>

FireworkSystem::FireworkSystem(ParticleForceRegistry* fR, const std::vector<ParticleForceGenerator*>& gen, const std::vector<RenderItem*>& sph, const std::vector<int>& sSizes, RenderItem* eS, std::list<ParticleExp>* pExps) {
	forceRegistry = fR;
	generators = gen;

	sphereSizes = sSizes;
	spheres = sph;

	expSphere = eS;

	particleExplosions = pExps;

	//Información sobre cada tipo de particula
	info = vector<typeInfo>(3);

	info[TYPE0] = {
		Vector3(0, 50 ,0),			//Vel
		Vector3(0, 0, 0),			//Acc
		{ 0.5, 0.25, 0, 1 },		//Color
		20,							//Size
		0.999,						//Damp
		1.5,						//MaxLifeTime
		1,							//MinLifeTime
		type::TYPE0,				//Tipo
		100,                         //Particulas al explotar
		15,  						//Vel min
		30,      					//Vel max
		type::TYPE1					//Tipo de particula que genera al explotar
	};

	info[TYPE1] = {
		Vector3(0, 0, 0),
		Vector3(0, 0, 0),
		{ 1, 1, 0, 1 },
		15,
		0.999,
		2,
		1.2,
		type::TYPE1,
		5,
		15,
		30,
		type::TYPE2
	};

	info[TYPE2] = {
		Vector3(0, 0, 0),
		Vector3(0, 0, 0),
		{ 0, 1, 1, 1 },
		9,
		0.999,
		1.5,
		1,
		type::TYPE2,
		0,
		15,
		30,
		type::NONE_TYPE
	};
}

FireworkSystem::~FireworkSystem() {
	for (auto a : fireworks) delete a;
}

void FireworkSystem::update(float t) {
	auto p = fireworks.begin();
	while (p != fireworks.end()) {

		if ((*p)->alive()) {
			(*p)->update(t);
			p++;
		}
		else {
			forceRegistry->deleteParticleRegistry(*p);
			explode(*p);
			delete* p;
			p = fireworks.erase(p);
		}
	}
}

void FireworkSystem::instantiateInitFirework() {
	auto type = info[TYPE0];
	createFirework(type, type.pos.p, type.vel);
}

void FireworkSystem::instantiateFirework(type t, Vector3 pos, Vector3 parentVel) {
	auto type = info[t];

	//Velocidad aleatoria en todas las direcciones mas velocidad del padre
	Vector3 vel;
	vel.x = (rand() % type.velMax) - type.velMin + parentVel.x;
	vel.y = (rand() % type.velMax) - type.velMin + parentVel.y;
	vel.z = (rand() % type.velMax) - type.velMin + parentVel.z;

	createFirework(type, pos, vel);
}

void FireworkSystem::explode(Firework* f) {
	if (info[f->getType()].childType != NONE_TYPE) {
		for (int i = 0; i < info[f->getType()].numFireworksToInstantiate; i++) {
			instantiateFirework(info[f->getType()].childType, f->getPosition(), f->getVel());
		}
	}
}

void FireworkSystem::createFirework(const typeInfo& type, Vector3 pos, Vector3 vel) {
	float lifeTime = type.minLifeTime + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (type.maxLifeTime - type.minLifeTime))); //Tiempo de vida aleatorio

	Firework* f = new Firework(pos, vel, type.acc, type.color, lifeTime, type.size, type.pType, type.numFireworksToInstantiate);

	ParticleGravity* gravity = new ParticleGravity(Vector3(0, -15, 0));
	ParticleWind* wind = new ParticleWind(Vector3(30, 0, 0), spheres, sphereSizes);
	ParticleExplosion* explosion = new ParticleExplosion(500, expSphere);
	ParticleDrag* drag = new ParticleDrag(0, 0);

	particleExplosions->push_back({ explosion, f });

	generators.push_back(gravity); generators.push_back(explosion); generators.push_back(wind); generators.push_back(drag);

	forceRegistry->add(f, wind);
	forceRegistry->add(f, gravity);
	forceRegistry->add(f, explosion);
	forceRegistry->add(f, drag);

	fireworks.push_back(f);
}
