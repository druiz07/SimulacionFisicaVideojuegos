#include "Particula.hpp"
#include "GeneradorSimple.hpp"
#include <list>
class Firework :public Particula
{


public:
	int update(double t);
	virtual Particula* clone() const;
	std::list<Particula*> explode();
	Firework(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, int nPExplosion, Vector4 c = { 0.4,0.3,0.4,1 }, double tA = 5);
private:
	std::list<std::shared_ptr<GeneradorSimple> >gens_; //metodo que da generadores


};
Firework::Firework(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, int nPExplosion, Vector4 c = { 0.4,0.3,0.4,1 }, double tA = 5)
	: Particula(p, initialSpeed, a, m, d, ri, c, tA)
{


}
int Firework::update(double t)
{

		return 0;
	
	return 1;
	//Dependiendo de lo que returnees eliminas o no el firework
}
std::list<Particula*> Firework::explode()
{
	/*
	* auto pShared =std::make_shared<Particula>(p);
		gens_.push_front(pShared);
	*/
	std::list<Particula*>listExp;
	for (int i = 0; i < nGen; i++)
	{
		//Tanto la velocidad como la direccion sera aleatoria 
		Vector3 dir2{ -1,0,0 };
		Vector3 pos{ 25,40,10 };

		//Aprovechar la posicion de firework para que parta mas o menos desde ahi
		//Particula* p = new Particula(pos + Vector3{ -100,0,-100 }, dir2, { 0.0,0.0,0.0 }, 1, 0.99, new RenderItem(CreateShape(PxSphereGeometry(2.25)), Vector4(1, 0, 1, 1)), Vector4{ 0.5,0.9,0.8,1 },5 );
		listExp.push_back(p);
	}
	return listExp;

}