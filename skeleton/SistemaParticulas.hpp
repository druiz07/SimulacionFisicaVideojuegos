
#include "Firework.hpp"
class SistemaParticulas
{
public:

	SistemaParticulas();
	void update(double t);
	void addGen(GeneradorSimple* g);

	GeneradorGaussiano* fireworkGen;
	std::vector<Firework*>fireworksPool;
	void generateFireworkSistem(Vector3 pos, Vector3 vel, Vector3 a, float m, float d, RenderItem* r, float sPart, int nD, Vector4 c, double tA, int nPG, string circulo ="nada");
	void shootFirework();


protected:
	std::list<Particula*>particulasGen;
	std::list<GeneradorSimple*>generadores;

};
SistemaParticulas::SistemaParticulas()
{
	
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

inline void SistemaParticulas::generateFireworkSistem(Vector3 pos,Vector3 vel,Vector3 a,float m, float d, RenderItem* r,float sPart,int nD,Vector4 c,double tA, int nPG,string circulo)
{
	particulasGen.push_back(new Firework(pos, vel,a, m, d, r, sPart, nD,c, tA, nPG,circulo));
	
}

