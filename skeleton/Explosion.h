#include "ForceGenerator.hpp";
#include "core.hpp"
class ExplosionGenerator : public ForceGenerator
{
public:

	ExplosionGenerator() {};
	virtual void updateForce(Particula* p, double t);
	void setIntensity(float i) { intensity = i; }
	void setTimeCt(float tC) { timeCt = tC; }
	void setExplosionCenter(Vector3 eC) { explosionCenter = eC; }
	void setRadius(float r) { radius = r; }
	void setctAnt(float in, float tc, Vector3 c,float r)
	{
		setIntensity(in);
		setTimeCt(tc);
		setExplosionCenter(c);
		setRadius(r);
	}
protected:
	float _k1;
	float _k2;
	float intensity;
	float radius;
	float timeCt;
	Vector3 explosionCenter;
};