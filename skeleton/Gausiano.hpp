#include "GeneradorSimple.hpp"
#include <time.h>
#include <random>

class GeneradorGaussiano: public GeneradorSimple
{

public:
	GeneradorGaussiano(Vector3 devpos, Vector3 devvel, std::string n,Vector3 mp, Vector3 mv);
	list<Particula*> generateParticles() override;
	~GeneradorGaussiano();

protected:

	Vector3 devpos;
	Vector3 devvel;
	std::mt19937 e2;
	int nPart = 50;

	std::normal_distribution<double>d{ 0,1 }; //Multiplicado por la varianza y sumas la media 


};
GeneradorGaussiano::GeneradorGaussiano(Vector3 dp, Vector3 dv,std::string n,Vector3 mp, Vector3 mv):GeneradorSimple(n)
{
	devpos = dp;
	devvel = dv;
	mediaPos = mp;
	mediaVel = mv;
	std::random_device r{};
	e2 = std::mt19937(r());
}
list<Particula*>GeneradorGaussiano::generateParticles()
{
	std::list<Particula*> pAux;

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

		pAux.push_back(new Particula(pos, vel, { 0.0,-10.0,0.0 }, 1, 0.99, new RenderItem(CreateShape(PxSphereGeometry(0.9)), Vector4(1, 0, 1, 1)), Vector4{ 0.5,0.9,0.8,1 }));


	}
	return pAux;

}
GeneradorGaussiano::~GeneradorGaussiano()
{

}