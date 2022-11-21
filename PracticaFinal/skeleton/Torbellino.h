#pragma once
#include "ParticleForceGenerator.h"
class Torbellino :public ParticleForceGenerator
{

public:

	Torbellino() {};
	Torbellino(const float k1, const float k2, float fuerza, Vector3 cT) :_k1(k1), _k2(k2), kF(fuerza), centroTorbellino(cT) {};
	virtual void updateForce(Particula* p, float t)
	{

		if (!p->hasFiniteMass()) return;





		Vector3 tVel;
		tVel.x = kF * (-(p->getPosition().z - centroTorbellino.z) - 0.2 * (p->getPosition().x - centroTorbellino.x));
		tVel.y = kF * (20 - (p->getPosition().y - centroTorbellino.y));
		tVel.z = kF * (p->getPosition().x - centroTorbellino.x) - 0.2 * (p->getPosition().z - centroTorbellino.z);
		Vector3 v = p->getVel() - tVel; //v seria -> getV- velViento , hacer que herede de la clase y un metodo para settear la velocidad , crear un genersdor con vientos 



		float drag_coef = v.normalize();
		Vector3 dragF;
		drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;

		dragF = -v * drag_coef;  //


		p->addForce(dragF);

	};
	void setTorbCentro(Vector3 c);
	void  setForce(float nForce) { kF = nForce; }
	void addForce(float addedForce) { kF = addedForce; }

protected:
	float _k1;
	float _k2;
	float kF;
	Vector3 centroTorbellino;



};

