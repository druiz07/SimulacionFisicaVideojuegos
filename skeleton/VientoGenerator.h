#include "ParticleDragGenerator.h"
class VientoGenerator :public ParticleDragGenerator
{
public:

	VientoGenerator() {};
	VientoGenerator(const float k1, const float k2) :_k1(k1), _k2(k2) {};
	void setk1k2(float k1k, float k2k) { _k1 = k1k; _k2 = k2k; }
	virtual void updateForce(Particula* p, float t);
	void setWindVel(Vector3 wV);
	

protected:
	float _k1;
	float _k2;
	Vector3 windVel;
};