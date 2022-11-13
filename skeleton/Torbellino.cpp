#include "Torbellino.h"
#include "Particula.h"
void Torbellino::updateForce(Particula* p, double t)
{


	if (fabs(p->inverse_mass) < 1e-10)return;





	Vector3 tVel;
	tVel.x = kF * (-(p->getPosition().z - centroTorbellino.z)- 0.2*(p->getPosition().x - centroTorbellino.x));
	tVel.y = kF * (20-(p->getPosition().y - centroTorbellino.y));
	tVel.z = kF*(p->getPosition().x- centroTorbellino.x) - 0.2 * (p->getPosition().z - centroTorbellino.z);
	Vector3 v = p->getVelocity() - tVel; //v seria -> getV- velViento , hacer que herede de la clase y un metodo para settear la velocidad , crear un genersdor con vientos 
	
	
	
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;

	dragF = -v * drag_coef;  //


	p->addForce(dragF);


};
void Torbellino::setTorbCentro(Vector3 c)
{
	centroTorbellino = c;
}