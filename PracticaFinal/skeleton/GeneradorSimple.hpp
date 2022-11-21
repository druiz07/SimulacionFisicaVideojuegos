#pragma once

#include <list>
using namespace std;
#include <string>
class GeneradorSimple
{
public:

	GeneradorSimple() {};
	virtual void generateParticles() = 0;

	Vector3 mediaPos;
	Vector3 mediaVel;
};

