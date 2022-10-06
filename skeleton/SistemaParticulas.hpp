#include "GeneradorSimple.hpp"

class SistemaParticulas
{
public:

	SistemaParticulas(double tA, Vector3 max_pos, Vector3 min_pos);

	void killParticles();
	void update(double t);
	bool checkPosAndTime(Vector3 pos) noexcept;
	void addGenerator(GeneradorSimple* g);



	

protected:
	std::list<Particula*>particulasGen;
	std::list<GeneradorSimple*>generadores;
	Vector3 gravity_;
	Vector3 max_pos;
	Vector3 min_pos;
	//En el update lo que haces es ver si las particulas se salen de la pantalla y recorrec los distintos generadores haciendo un generate 
	//Las particulas se borran de foma normal 

};
SistemaParticulas::SistemaParticulas(double tA, Vector3 maxpos, Vector3 minpos)
{

	max_pos = maxpos;
	min_pos = minpos;

}
bool SistemaParticulas::checkPosAndTime(Vector3 pos)noexcept
{
	//Tiene que estar todas las componentes entre la minima y la maxima?
	return true;
}
void SistemaParticulas::update(double t)
{
	for (auto i : generadores)
	{
		particulasGen = i->generateParticles();//Obrtenemos la lista de particulas
		auto it = particulasGen.begin();
		for (auto a : particulasGen)
		{
			/*if (!checkPosAndTime(a->getPosition())) //La particula podria devolver su tiempo de vida 
			{
				
				it=particulasGen.erase(it);
			}
			else*/ 
			a->integrate(t);
			it++;

			
		}
	}
}
void SistemaParticulas::addGenerator(GeneradorSimple* g)
{
	generadores.push_back(g);

}

