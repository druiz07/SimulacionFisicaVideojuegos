#pragma once
#include "Particula.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

enum type { TYPE0, TYPE1, TYPE2, NONE_TYPE };

class Firework : public Particula {
public :
	Firework(Vector3 Pos, Vector3 vel, Vector3 ac, Vector4 color, float lT, float size, type t, int numP, double damp = 0.999);
	type getType();

private:
	type type_;
};
