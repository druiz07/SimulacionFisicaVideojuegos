#include "VientoGenerator.h"
#include "Particula.h"
void VientoGenerator::updateForce(Particula* p, double t)
{


	if (fabs(p->inverse_mass) < 1e-10)return;

	Vector3 v = p->getVelocity()-windVel;
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;

	dragF = -v * drag_coef;  //


	p->addForce(dragF);


};
void VientoGenerator::setWindVel(Vector3 wV)
{
	windVel = wV;
}