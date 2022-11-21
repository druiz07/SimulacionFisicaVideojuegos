#pragma once
#include "GeneradorSimple.hpp"
#include <time.h>
#include <random>
#include "RenderUtils.hpp"
#include "Particula.h"
class GeneradorGaussiano : public GeneradorSimple
{

public:
	GeneradorGaussiano(Vector3 devpos, Vector3 devvel, std::string n, Vector3 mp, Vector3 mv, Vector4 pc, int nPart, int tA);
	void  generateParticles();

	void update(float t);
	~GeneradorGaussiano();
	list<Particula*> particulas;

protected:

	Vector3 devpos;
	Vector3 devvel;
	Vector4 particlecolor;
	std::mt19937 e2;
	int nPart;
	float gravity = -10.0;
	int timeAlive;
	float cadencia = timeAlive;
	std::normal_distribution<double>d{ 0,1 }; //Multiplicado por la varianza y sumas la media 


};
GeneradorGaussiano::GeneradorGaussiano(Vector3 dp, Vector3 dv, std::string n, Vector3 mp, Vector3 mv, Vector4 pc, int nP, int tA) :GeneradorSimple(n)
{
	devpos = dp;
	devvel = dv;
	mediaPos = mp;
	mediaVel = mv;
	particlecolor = pc;
	nPart = nP;
	timeAlive = tA;
	std::random_device r{};
	e2 = std::mt19937(r());
}
void GeneradorGaussiano::generateParticles()
{


	for (int i = 0; i < nPart; i++)
	{


		Vector3 vel{ (float)d(e2),(float)d(e2) ,(float)d(e2) }; //= d(e2) * devvel + mediaVel;
		Vector3 pos{ (float)d(e2),(float)d(e2) ,(float)d(e2) }; // d(e2) * devpos + mediaPos;
		vel.x = vel.x * devvel.x + mediaVel.x;
		vel.y = vel.y * devvel.y + mediaVel.y;
		vel.x = vel.z * devvel.z + mediaVel.z;


		pos.x = pos.x * devpos.x + mediaPos.x;
		pos.y = pos.y * devpos.y + mediaPos.y;
		pos.x = pos.z * devpos.z + mediaPos.z;
		//pos, vel, { 0.0,0.0,0.0 }, 0.2, 0.99, new RenderItem(CreateShape(PxSphereGeometry(2)), Vector4(1, 0, 1, 1)), aSp, timeAlive, particlecolor
		Particula* p = new Particula(pos, vel, { 0.0,0.0,0.0 }, { 0.4,0.1,0.75,1 },10,2,1);
		particulas.push_back(p);


	}


}

void GeneradorGaussiano::update(float t) {

	auto p = particulas.begin();
	while (p != particulas.end()) {

		if ((*p)->alive()) {
			(*p)->update(t);
			p++;
		}
		else {
			
			delete* p;
			p = particulas.erase(p);
		}
	}

	timeAlive -= t;
	if (timeAlive < 0) {
		generateParticles();
		timeAlive = cadencia;
	}
}
GeneradorGaussiano::~GeneradorGaussiano()
{
	for (auto a : particulas) delete a;
}