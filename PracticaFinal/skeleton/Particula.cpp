#pragma once
#include "Particula.h"
#include <iostream>
#include "ParticleForceRegistry.h"

Particula::Particula(Vector3 p, Vector3 v, Vector3 ac, Vector4 c, float lT, float size, float mass) {
	vel = v;
	acc = ac;

	pos = physx::PxTransform(p.x, p.y, p.z);

	renderI = new RenderItem(CreateShape(physx::PxSphereGeometry(size/10)), &pos, c);

	lifeTime = lT;

	dead = false;

	force = Vector3(0, 0, 0);

	inverse_mass = 1 / mass;
}

Particula::~Particula() {
	DeregisterRenderItem(renderI);
}

void Particula::update(double t) {
	
	lifeTime -= t;
	if (lifeTime <= 0) {
		dead = true;
		return;
	}

	

	Vector3 a = acc;
	a += force * inverse_mass;

	vel += a * t;
	pos.p += vel * t;
	clearForce();
}

float Particula::getLifeTime() {
	return lifeTime;
}

void Particula::setLifeTime(float lT) {
	lifeTime = lT;
}

void Particula::setPosition(Vector3 p) {
	pos.p = p;
}

void Particula::setColor(Vector4 color) {
	renderI->color = color;
}

void Particula::setdepthVol(float d, float v)
{
	maxDepth = d;
	volume = v;
}

Vector3 Particula::getPosition() {
	return pos.p;
}

Vector3 Particula::getVel() {
	return vel;
}

float Particula::getDepth()
{
	return maxDepth;
}

float Particula::getVolume()
{
	return volume;
}

bool Particula::alive() {
	return !dead;
}

bool Particula::hasFiniteMass() {
	return (inverse_mass != 0);
}

float Particula::getMass() {
	return 1 / inverse_mass;
}

void Particula::clearForce() {
	force = Vector3(0, 0, 0);
}

void Particula::addForce(const Vector3& f) {
	force += f;
}

void Particula::addForceRegistry(ParticleForceGenerator* p) {
	forcesRegistries.push_back(p);
}

vector<ParticleForceGenerator*>& Particula::getForcesRegistries() {
	return forcesRegistries;
}

