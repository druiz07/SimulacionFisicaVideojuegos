
#include "Firework.hpp"
class SistemaParticulas
{
public:

	SistemaParticulas();
	void update(double t);
	void addGen(GeneradorSimple* g);

	GeneradorGaussiano* fireworkGen;
	std::vector<Firework*>fireworksPool;
	void generateFireworkSistem();
	void shootFirework();


protected:
	std::list<Particula*>particulasGen;
	std::list<GeneradorSimple*>generadores;

};
SistemaParticulas::SistemaParticulas()
{
	generateFireworkSistem();
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

	list<Particula*>::iterator it = particulasGen.begin();
	while (it != particulasGen.end())
	{
		
		if (*it != NULL) {
			(*it)->integrate(t);
			if (!(*it)->isAlive()||!(*it)->checkSpace())
			{

				auto cast = dynamic_cast<Firework*>(*it);
				if (cast != nullptr) {
					auto a= cast->explode();
					if(a.size()>0)particulasGen.insert(particulasGen.begin(), a.begin(), a.end());
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

inline void SistemaParticulas::generateFireworkSistem()
{
	//new RenderItem(CreateShape(PxSphereGeometry(sizeF)), Vector4(1, 0, 1, 1)), sizeF,nGeneraciones-1, Vector4{ 0.5,0.9,0.8,1 }, nPart);


	particulasGen.push_back(new Firework(Vector3{ 0,0,-15 }, { 0,30,0 }, Vector3{ 0,-10,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(2)), Vector4(1, 0, 1, 1)), 1.5, 3, Vector4{ 0.2,0.2,0.5,1 }, 4, 3));
	
	//particulasGen.push_back(new Firework(Vector3{ 0,0,15 }, { 0,30,0 }, Vector3{ 0,-10,0 },1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(1.5)), Vector4(1, 0, 1, 1)), 1.1,3, Vector4{ 0.5,0.9,0.8,1 }, 3,9));

}

