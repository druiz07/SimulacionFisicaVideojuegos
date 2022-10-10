#include "Proyectil.hpp"
#include <list>
using namespace std;


class GeneradorSimple
{
public:

	GeneradorSimple(std::string n);
	virtual list<Particula*>generateParticles() = 0;
	std::string nombreGenerador;
	bool isActive;
	Vector3 mediaVel;
	Vector3 mediaPos;

};
GeneradorSimple::GeneradorSimple(std::string n)
{
	nombreGenerador=n;
}
