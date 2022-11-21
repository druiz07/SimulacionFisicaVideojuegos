#include "Firework.h"

Firework::Firework(Vector3 Pos, Vector3 vel, Vector3 ac, Vector4 color, float lT, float size, type t, int numP, double damp)
																 : Particula(Pos, vel, ac, color, lT, size, damp) {

	type_ = t;
}

type Firework::getType() {
	return type_;
}
