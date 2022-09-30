#include "GeneradorSimple.hpp"

class SistemaParticulas
{
public:

	SistemaParticulas(double tA);
	
	void killParticles();
	void update(double t);

	double timeAlive;  //Cuando se resta es -- a secas

protected:
	std::list<Particula*>particulas;
	std::list<GeneradorSimple*>particulas;
	Vector3 gravity_;
	Vector3 max_pos;
	Vector3 min_Pos;
	//En el update lo que haces es ver si las particulas se salen de la pantalla y recorrec los distintos generadores haciendo un generate 
	//Las particulas se borran de foma normal 

};
SistemaParticulas::SistemaParticulas(double tA)
{
}
	
