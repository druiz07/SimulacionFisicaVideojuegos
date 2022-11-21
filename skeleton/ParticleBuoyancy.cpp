#include "ParticleBuoyancy.h"

void ParticleBuoyancy::updateForce(Particula* p, float t) {
	float depth;
	auto pCast = dynamic_cast<ParticulaBote*>(p);
	depth = p->getPosition().y;
	Vector3 f(0.0f, 0.0f, 0.0f);
	if (depth > (waterHeight + pCast->maxdepth)) {
		p->setColor({ 1,0,0,1 });
		return;
	}
	if (depth < (waterHeight - pCast->maxdepth)) {
		p->setColor({ 1,0,1,1 });
		f.y = liquidDensity * pCast->volume;
	}
	else {
		float depthExt = waterHeight + pCast->maxdepth;
		float volFactor = (depthExt - depth) / (2 * pCast->maxdepth);
		f.y = liquidDensity * pCast->volume * volFactor;
		p->setColor({ 0.5,0,1,1 });
	}
	p->addForce(f);
}
