#pragma once
#include <list>
#include <vector>
#include "RenderUtils.hpp"
#include "core.hpp"
class ParticleForceGenerator;
using namespace std;

class Particula {

public:
	Particula(Vector3 Pos, Vector3 vel, Vector3 ac, Vector4 color, float lT, float size, float mass);
	~Particula();

	void update(double t);
	float getLifeTime();
	void setLifeTime(float lT);
	void setPosition(Vector3 pos);
	void setColor(Vector4 color);
	void setdepthVol(float d, float v);
	Vector3 getPosition();
	Vector3 getVel();
	float getDepth();
	float getVolume();

	bool alive();
	bool hasFiniteMass();
	float getMass();

	void clearForce();
	void addForce(const Vector3& f);
	void addForceRegistry(ParticleForceGenerator* p);
	vector<ParticleForceGenerator*>& getForcesRegistries();

protected:
	Vector3 vel;
	Vector3 acc;
	Vector4 color;
	float maxDepth=0;
	float volume=0;
	
	Vector3 force;
	float inverse_mass;

	physx::PxTransform pos;

	RenderItem* renderI;

	float lifeTime;
	bool dead;

	vector<ParticleForceGenerator*> forcesRegistries;
};

