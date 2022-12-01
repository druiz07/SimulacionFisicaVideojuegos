#pragma once
#include "Particula.h"
#include "ParticleForceGenerator.h"
#include "BodyForceGenerator.h"
#include "BodyExplosion.h"
#include <map>


typedef std::pair<ParticleForceGenerator*, Particula*>FRPair;
class ParticleForceRegistry :public std::multimap<ParticleForceGenerator*, Particula*>
{

	struct BodyForceRegistration
	{
		SolidBody* body;
		BodyForceGenerator* bfg;
	};
	typedef std::vector<BodyForceRegistration> BodyRegistry;
	BodyRegistry bodyRegistrations;


public:

	ParticleForceRegistry& getRegistrations() {
		return *this;
	}
	void updateForces(double duration)
	{
		for (auto it = begin(); it != end(); it++)
		{

			it->first->updateForce(it->second, duration);
		}
	};
	void add(Particula* p, ParticleForceGenerator* fg)
	{
		this->insert(FRPair(fg, p));
		p->addForceRegistry(fg);
	}
	void deleteParticleRegistry(Particula* p)
	{
		for (auto it = begin(); it != end(); )
		{
			if (it->second == p)it = this->erase(it);
			else it++;

		}


	}
	void clear() {
		clear();
	}

	//METODOS PARA LOS CUERPOS RIGIDOS

	BodyRegistry& getBodyRegistrations() {
		return bodyRegistrations;
	}

	void addBodyForce(const std::vector<SolidBody*>& bodies, BodyForceGenerator* bfg) {
		for (auto b : bodies) {

			b->bodyForcesRegistries.push_back(bfg);
			bodyRegistrations.push_back({ b, bfg });
		}
	}
	void addBodyExplosionForce(const std::vector<SolidBody*>& bodies, int force) {
		for (auto b : bodies) {
			auto e = new BodyExplosion(force);

			b->bodyForcesRegistries.push_back(e);
			bodyRegistrations.push_back({ b, e });
			b->bodyExplosionForce = e;
		}
	}

	void clearBodyForces() {
		bodyRegistrations.clear();
	}

	void updateBodyForces(float t) {
		for (auto it = bodyRegistrations.begin(); it != bodyRegistrations.end(); ++it) {
			it->bfg->updateForce(it->body, t);
		}
	}

	void removeBodyForces(SolidBody* body) {

		auto forcesRegistries = body->bodyForcesRegistries;

		for (int i = forcesRegistries.size() - 1; i >= 0; i--) {
			for (int c = bodyRegistrations.size() - 1; c >= 0; c--) {
				if (bodyRegistrations[c].bfg == forcesRegistries[i]) {
					bodyRegistrations.erase(bodyRegistrations.begin() + c);
				}
			}
		}
		forcesRegistries.clear();
	}
};









/*
class ParticleForceRegistry
{
protected:
	// Storage for generator-particle entry
	struct ParticleForceRegistration
	{
		Particula* particula;
		ParticleForceGenerator* fg;
	};
	typedef std::vector<ParticleForceRegistration> Registry;
	Registry registrations;



public:

	//METODOS PARA LAS PARTICULAS

	ParticleForceRegistry() {};

	Registry& getRegistrations() {
		return registrations;
	}


	// Removes all associations. Particle and Generators won't be deleted
	void clear() {
		registrations.clear();
	}
	// Update all the generators in the registry
	void updateForces(float t) {
		for (auto it = registrations.begin(); it != registrations.end(); ++it) it->fg->updateForce(it->particula, t);
	}

	void remove(Particula* particula) {

		auto forcesRegistries = particula->getForcesRegistries();

		for (int i = forcesRegistries.size() - 1; i >= 0; i--) {
			for (int c = registrations.size() - 1; c >= 0; c--) {
				if (registrations[c].fg == forcesRegistries[i]) {
					registrations.erase(registrations.begin() + c);
				}
			}
		}
		forcesRegistries.clear();
	}



};











*/