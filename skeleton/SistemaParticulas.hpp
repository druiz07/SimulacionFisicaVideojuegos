
#include "Firework.hpp"
class SistemaParticulas
{
public:

	SistemaParticulas(Vector3 maxpos, Vector3 minpos, GeneradorSimple* g);
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
SistemaParticulas::SistemaParticulas(Vector3 maxpos, Vector3 minpos, GeneradorSimple* g)
{

	//fireworkGen=

	generadores.push_back(g);
	generateFireworkSistem();
	//Particula* p = fireworksPool.front()->clone();

	particulasGen.push_back(p);

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
					particulasGen.insert(particulasGen.begin(),a.begin(), a.end());
				}
				delete *it;
				it = particulasGen.erase(it);
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


	std::shared_ptr<GeneradorGaussiano>gen1(new GeneradorGaussiano({0.2,0.1,0.1}, {.1,.1,.1}, "Gaussiano1", {25,40,0}, {2,25,0}, {0.1,0.2,0.7,1}, 1, 6));//new
	fireworksPool.push_back(new Firework(Vector3{ 0,0,0 }, { 10,10,10 }, Vector3{ 2,2,2 }, 2, 0.98, new RenderItem(CreateShape(PxSphereGeometry(0.9)), Vector4(1, 0, 1, 1)), { gen1 }));





}

