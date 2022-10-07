#include "Particula.hpp"
#include <list>

class GeneradorSimple
{
public:

	GeneradorSimple(std::string n, Vector3 mp, Vector3 mv);
	virtual std::list<Particula*>generateParticles() = 0;
	std::string nombreGenerador;
	bool isActive;
	Vector3 mediaVel;
	Vector3 mediaPos;
};
GeneradorSimple::GeneradorSimple(std::string n, Vector3 mp, Vector3 mv)
{
	nombreGenerador = n;
	mediaVel = mv;
	mediaPos = mp;
}
