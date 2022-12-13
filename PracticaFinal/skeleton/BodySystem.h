#pragma once
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include "SolidBody.h"
#include "ParticleForceRegistry.h"

class BodySystem {
public:
	BodySystem(PxScene* _scene, PxPhysics* _physics, ParticleForceRegistry* _forceRegistry, PxTransform _p, physx::PxMaterial* mat = nullptr, float _step = 1.5, bool _colorR = true, float _life = 10, float _size = 3, int _max = 20, Vector4 _color = { 1,0,0,1 }) {
		scene = _scene; physics = _physics; p = _p; step = _step; colorR = _colorR; 
		life = _life; size = _size; max = _max; color = _color; timeSiceAdded = 0;
		m = mat;
		numBodies = 0; forceRegistry = _forceRegistry;

		srand(time(NULL));
	}
	~BodySystem() {
		for (auto b : bodies) delete b;
	}
	void addBody() {
		if (colorR) {
			color = { (float(rand() % 10)) / 10.0f, (float(rand() % 10)) / 10.0f , (float(rand() % 10)) / 10.0f , 1 };
		}

		SolidBody* body = new SolidBody();
		body->rigid = physics->createRigidDynamic(p);
		auto e=m->getRestitution();
		PxShape* shape = CreateShape(PxBoxGeometry(size, size, size), m);
		body->rigid->attachShape(*shape);

		Vector3 vel = { -5.0f + rand() / (RAND_MAX / (10.0f)), -5.0f + rand() / (RAND_MAX / (10.0f)) , -5.0f + rand() / (RAND_MAX / (10.0f)) };
		body->rigid->setLinearVelocity(vel);
		int massRand= rand();
		while (massRand > 10 || massRand < 2)
		{
			massRand = rand();
		}
		body->rigid->setMass(massRand);
		

		if(inertia==0)PxRigidBodyExt::updateMassAndInertia(*body->rigid, size * size * size);
		else PxRigidBodyExt::updateMassAndInertia(*body->rigid, inertia);



		scene->addActor(*body->rigid);
		body->isnew = true;
		body->life = life;
		body->force = { 0.0, 0.0, 0.0 };
		body->torque = { 0.0, 0.0, 0.0 };
		body->item = new RenderItem(shape, body->rigid, color);

		bodies.push_back(body);

		numBodies++;
		timeSiceAdded = 0;

	}
	void update(float t) {
		timeSiceAdded += t;
		if (timeSiceAdded > step && numBodies < max) addBody();

		for (int i = bodies.size() - 1; i >= 0; i--) {
			auto body = bodies.at(i);

			body->rigid->addForce(body->force, PxForceMode::eFORCE);
			body->force = { 0.0, 0.0, 0.0 };
			body->rigid->addTorque(body->torque);
			body->torque = { 0.0, 0.0, 0.0 };
			body->life -= t;

			if (body->life < 0) {
				forceRegistry->removeBodyForces(body);
				auto bodyToDelete = bodies.begin() + i;
				delete *(bodyToDelete);
				bodies.erase(bodyToDelete);
				numBodies--;
			}
		}
	}
	void setInertiaSize(float i,float s)
	{
		inertia = i;
		size =s;
	}
	std::vector<SolidBody*>& getBodies() {
		return bodies;
	}

private:
	std::vector<SolidBody*> bodies;
	ParticleForceRegistry* forceRegistry;
	PxScene* scene;
	PxPhysics* physics;
	PxTransform p;
	float step;
	bool colorR;
	float life;
	float size;
	float inertia=0;
	int max;
	Vector4 color;
	physx::PxMaterial* m;

	float timeSiceAdded;
	int numBodies;
};
