#pragma once
#include "Particula.h"
#include "ParticleForceGenerator.h"
#pragma once
#include <map>


typedef std::pair<ParticleForceGenerator*, Particula*>FRPair;
class ParticleForceRegistry :public std::multimap<ParticleForceGenerator*, Particula*>
{

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