#pragma once
#include "ForceGenerator.hpp"
#include "core.hpp"
class GravityForceGenerator :public ForceGenerator
{
public:

	GravityForceGenerator(const Vector3& g);
	virtual void updateForce(Particula* p, double delta);
	inline void setGravity(Vector3 g) { gravity = g; };

protected:
	Vector3 gravity;
};
void GravityForceGenerator::updateForce(Particula* p, double delta)
{
	if (fabs(p->inverse_mass) < 1e-10);
	return;
	p->addForce(gravity * p->mass);
 }