#include "Particula.hpp"
#include <list>

class GeneradorSimple
{
public:

	GeneradorSimple(std::string n);
	virtual std::list<Particula*>generateParticles() = 0;
	std::string nombreGenerador;
	bool isActive;


};
GeneradorSimple::GeneradorSimple(std::string n)
{
	nombreGenerador=n;
}
