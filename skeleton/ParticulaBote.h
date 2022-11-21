#pragma once
#include "Particula.h"
#include "core.hpp"
using namespace physx;

class ParticulaBote:public Particula
{
public:
	ParticulaBote() {};

	ParticulaBote(float den, float v, Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, Vector3 posSpace, Vector4 c = { 0.4,0.3,0.4,1 }, double tA = 5);
//Particula(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, Vector3 posSpace, Vector4 c = { 0.4,0.3,0.4,1 }, double tA = 5)

	float volume;
	float maxdepth;
};

