#pragma once
#include <map>
#include "ForceGenerator.hpp";

typedef std::pair<ForceGenerator*, Particula*>FRPair;
class ParticleForceRegistry :public std::multimap<ForceGenerator*, Particula*>
{
public:

	void updateForces(double duration)
	{
		for (auto it = begin(); it != end(); it++)
		{
			
		it->first->updateForce(it->second, duration);
		}
	};
	void addRegistry(ForceGenerator* fg, Particula* p)
	{
		this->insert( FRPair(fg, p) );
	}
	void deleteParticleRegistry( Particula* p)
	{
		for (auto it = begin(); it != end(); )
		{
			if (it->second == p)it = this->erase(it);
			else it++;

		}


	}

};