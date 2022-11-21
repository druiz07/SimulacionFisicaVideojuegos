#pragma once
#include "ParticleForceGenerator.h"
#include "Particula.h"
#include <vector>
using namespace std;

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

enum SphereType { RIGHTDIRWIND, LEFTDIRWIND , RANDOMDIRWIND};

class ParticleWind : public ParticleForceGenerator
{
private:
	// Acceleration for gravity
	Vector3 f;

	//Tiempos para cambios de aceleración de la tercera esfera
	float timeChangeDir = 0.1;
	float time = 0;

	std::vector<RenderItem*> spheres;
	std::vector<int> sphereSizes;

	bool pointSphere(Vector3 pointPos, const physx::PxTransform* sphereTransform, int i) {
		return sphereSizes[i] > sqrt(pow(pointPos.x - sphereTransform->p.x, 2) + pow(pointPos.y - sphereTransform->p.y, 2) + pow(pointPos.z - sphereTransform->p.z, 2));;
	}

public:
	ParticleWind(const Vector3& force, const std::vector<RenderItem*>& sph, const std::vector<int>& sSizes) : f(force), spheres(sph), sphereSizes(sSizes) {}


	virtual void updateForce(Particula* particle, float t) {
		if (!particle->hasFiniteMass()) return;

		for (int i = 0; i < spheres.size(); i++) {
			if (i == SphereType::RIGHTDIRWIND) {
				if (pointSphere(particle->getPosition(), spheres[i]->transform, i)) {
					particle->addForce(f * particle->getMass());
				}
			}
			else if(i == SphereType::LEFTDIRWIND){
				Vector3 auxF = f; auxF.x = -auxF.x;
				if (pointSphere(particle->getPosition(), spheres[i]->transform, i)) {
					particle->addForce(auxF * particle->getMass());
				}
			}
			else if (i == SphereType::RANDOMDIRWIND) {
				time -= t;
				if (time < timeChangeDir) {
					time = timeChangeDir;

					float x = -10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20)));
					float y = -10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20)));
					float z = -10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20)));

					Vector3 auxF = Vector3(x,y,z);
					if (pointSphere(particle->getPosition(), spheres[i]->transform, i)) {
						particle->addForce(auxF/t * particle->getMass());
					}
				}
			}
		}
	}
};
