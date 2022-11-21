#include "ParticleDragGenerator.h"
#include "Particula.h"
void ParticleDragGenerator::updateForce(Particula* p, float t)
{


	if (fabs(p->inverse_mass) < 1e-10)return;

	Vector3 v = p->getVelocity(); //v seria -> getV- velViento , hacer que herede de la clase y un metodo para settear la velocidad , crear un genersdor con vientos 
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;

	dragF = -v * drag_coef;  //


	p->addForce(dragF);


}