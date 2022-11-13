#include "Explosion.h"
#include "Particula.h"
#include <cmath>
void ExplosionGenerator::updateForce(Particula* p, double t)
{


	if (fabs(p->inverse_mass) < 1e-10)return;

	float r = sqrt(pow(p->getPosition().x - explosionCenter.x, 2) + pow((p->getPosition().y - explosionCenter.y), 2) + pow((p->getPosition().z - explosionCenter.z), 2));
	if (r < radius)
	{
		float result = intensity / pow(r, 2);
		Vector3 force{ result * (p->getPosition().x - explosionCenter.x)
		 ,result * (p->getPosition().y - explosionCenter.y)
		 ,result * (p->getPosition().z - explosionCenter.z)
		};
		force *= exp(-(t / timeCt));
		p->addForce(force);
	}
	else
	{
		Vector3 force{ 0,0,0 };
		p->addForce(force);
	}


	


}