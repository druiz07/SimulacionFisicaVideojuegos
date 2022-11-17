
#include "Particula.h"
Particula::Particula(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, Vector3 posSpace, Vector4 c = { 0.4,0.3,0.4,1 }, double tA = 5)
{
	position = PxTransform(p.x, p.y, p.z);
	speed = initialSpeed;
	acceleration = a;
	isAlive_ = true;
	actionSpace = posSpace;

	renderItem = ri;
	renderItem->transform = &position;
	renderItem->color = c;
	timeAlive = tA;
	damping = d;   //Rozamiento entre 0 y 1
	force = { 0,0,0 };
	mass = m;
	inverse_mass = (1 / mass);

}



 void Particula::integrate(float deltaTime)
{

	if (inverse_mass <= 0.0f) return;

	timeAlive -= deltaTime;
	if (timeAlive < 0)isAlive_ = false;

	position.p += (speed * deltaTime);
	Vector3 totalAcceleration = acceleration;
	totalAcceleration += force * inverse_mass; // calculate the reciprocal of the mass.;
	speed += totalAcceleration * deltaTime;
	speed *= powf(damping, deltaTime);
	clearForce();

}





void Particula::setPosition(Vector3 p)
{
	position.p = p;
}

void Particula::setMass(float mass)
{
	mass = mass;
}

void Particula::setVelocity(Vector3 s)
{
	speed = s;
}

void Particula::setAcceleration(Vector3 a)
{
	acceleration = a;
}

void Particula::setDamping(float d)
{
	damping = d;
}

void Particula::setColor(Vector4 color)
{
	renderItem->color = color;
}

void Particula::setSize(const float size)
{
	renderItem->shape = CreateShape(PxSphereGeometry(size));
}

 bool Particula::checkSpace()
{
	if (position.p.x > actionSpace.x || position.p.y > actionSpace.y || position.p.z > actionSpace.z)return false;
	else if (position.p.x < -actionSpace.x || position.p.y < -actionSpace.y || position.p.z < -actionSpace.z)return false;;
	return true;

}

inline Particula* Particula::clone(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, Vector3 posSpace, Vector4 c, double tA)
{
	return new Particula(p, initialSpeed, a, m, d, ri, posSpace, c = { 0.4,0.3,0.4,1 }, tA = 5);
}

void Particula::setParticle(Vector3 pos, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, Vector3 posSpace, double ta, Vector4 c = { 0.4,0.3,0.4,1 })
{
	position = PxTransform(pos.x, pos.y, pos.z);
	speed = initialSpeed;
	acceleration = a;

	this->mass = m;

	renderItem = ri;
	renderItem->transform = &position;
	renderItem->color = c;
	timeAlive = ta;
	actionSpace = posSpace;
	inverse_mass = (1 / mass);
	damping = d;   //Rozamiento entre 0 y 1
}

void Particula::clearForce()
{
	force = Vector3(0);

};
void Particula::addForce(const Vector3& f)
{

	force += f;

};



Vector3 Particula::getPosition() const
{
	return position.p;
}

float Particula::getMass() const
{
	return mass;
}

Vector3 Particula::getVelocity() const
{
	return speed;
}

Vector3 Particula::getAcceleration() const
{
	return acceleration;
}

float Particula::getDamping() const
{
	return damping;
}

Particula::~Particula()
{
	DeregisterRenderItem(renderItem);
}
bool Particula::isAlive()
{
	return isAlive_;
}