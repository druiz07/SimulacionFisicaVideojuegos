#pragma once
#include "SolidBody.h"

class BodyForceGenerator
{
public:
	// Overload to provide functionality
	virtual void updateForce(SolidBody* solidBody, float t) = 0;
};
