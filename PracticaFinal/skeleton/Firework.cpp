#include "Firework.h"
#include "FireworkSystem.h"
Firework::Firework(Vector3 Pos, Vector3 vel, Vector3 ac, Vector4 color, float lT, float size, type t, int numP, double damp)
	: Particula(Pos, vel, ac, color, lT, size, damp) {

	type_ = t;
}

type Firework::getType() {
	return type_;
}
void Firework::explode(FireworkSystem* pS) {

	if (pS->info[getType()].childType != NONE_TYPE) {
		for (int i = 0; i < pS->info[getType()].numFireworksToInstantiate; i++) {
			pS->instantiateFirework(pS->info[getType()].childType, getPosition(), getVel());
		}
	}
}