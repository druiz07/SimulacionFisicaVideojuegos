#include "ParticulaBote.h"
ParticulaBote::ParticulaBote(float den, float v, Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, Vector3 posSpace, Vector4 c,double tA):Particula(p,initialSpeed,a,m,d,ri,posSpace,c,tA)
{
	volume = v;
	maxdepth= den;
}