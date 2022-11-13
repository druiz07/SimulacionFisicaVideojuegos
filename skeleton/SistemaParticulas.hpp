#pragma once
#include "Firework.hpp"
#include "ParticleForceRegistry.hpp";
#include "GravityForceGenerator.hpp"
#include "Explosion.h"

class SistemaParticulas
{
public:

	SistemaParticulas();
	void update(double t);
	void addGen(GeneradorSimple* g);

	GeneradorGaussiano* fireworkGen;
	std::vector<Firework*>fireworksPool;
	void generateFireworkSistem(Vector3 pos, Vector3 vel, Vector3 a, float m, float d, RenderItem* r, float sPart, int nD, Vector4 c, double tA, int nPG, string circulo = "nada");
	//void shootFirework();


protected:
	std::list<Particula*>particulasGen;
	std::list<GeneradorSimple*>generadores;
	ExplosionGenerator* eG;
	GravityForceGenerator* g;
	ParticleForceRegistry pfR;
};
SistemaParticulas::SistemaParticulas()
{
	eG = new ExplosionGenerator();
	eG->setctAnt(15, 3, { 10,0,0 }, 25);//intensidad 10 desde el 000 radio 10 y de tiempo 5

	Particula* p = new Particula({ 5,0,0 }, { 0,0,0 }, Vector3{ 0,0,0 }, 0.2, 0.98, new RenderItem(CreateShape(PxSphereGeometry(2)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.2,0.2,0.5,1 }, 50);

	Particula* p2 = new Particula({ 7,0,0 }, { 0,0,0 }, Vector3{ 0,0,0 }, 4, 0.98, new RenderItem(CreateShape(PxSphereGeometry(1)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.8,0.5,0.2,1 }, 50);
	pfR.addRegistry(eG, p);
	pfR.addRegistry(eG, p2);

	particulasGen.push_back(p);
	particulasGen.push_back(p2);

}
void SistemaParticulas::update(double t)
{

	for (auto i : generadores)
	{
		if (i != NULL) {
			auto aux = i->generateParticles();//Obrtenemos la lista de particulas
			for (auto a : aux)
			{
				particulasGen.push_back(a);
			}
		}
	}
	pfR.updateForces(t);
	list<Particula*>::iterator it = particulasGen.begin();
	while (it != particulasGen.end())
	{

		if (*it != NULL) {
			(*it)->integrate(t);
			if (!(*it)->isAlive() || !(*it)->checkSpace())
			{

				auto cast = dynamic_cast<Firework*>(*it);
				if (cast != nullptr) {
					auto a = cast->explode();
					if (a.size() > 0)particulasGen.insert(particulasGen.begin(), a.begin(), a.end());
					a.clear();
				}
				if (*it != nullptr) {
					delete* it;
					it = particulasGen.erase(it);
				}
			}
			else it++;
		}
	}

}
void SistemaParticulas::addGen(GeneradorSimple* g)
{

	generadores.push_back(g);
}

inline void SistemaParticulas::generateFireworkSistem(Vector3 pos, Vector3 vel, Vector3 a, float m, float d, RenderItem* r, float sPart, int nD, Vector4 c, double tA, int nPG, string circulo)
{
	particulasGen.push_back(new Firework(pos, vel, a, m, d, r, sPart, nD, c, tA, nPG, circulo));

}

