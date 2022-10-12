#include "RenderUtils.hpp"
#include "core.hpp"
#include <iostream>


using namespace physx;

class Particula
{
public:

	PxTransform position;
	Vector3 speed;
	Vector3 acceleration;

	double timeAlive;  //Cuando se resta es -- a secas
	bool isAlive_;


	float mass, damping;
	RenderItem* renderItem;

	Particula() noexcept {};
	void setPosition(Vector3 position);
	void setMass(float mass);
	void setVelocity(Vector3 s);
	void setAcceleration(Vector3 a);
	void setDamping(float d);
	void setColor(Vector4 color);
	void setSize(const float size);

	bool isAlive();
	void setParticle(Vector3 pos, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, double timeAlive, Vector4 color);

	Vector3 getPosition() const;
	float getMass() const;
	Vector3 getVelocity() const;
	Vector3 getAcceleration() const;
	float getDamping() const;

	Particula(Vector3 position, Vector3 initialSpeed, Vector3 acceleration, float mass, float damping, RenderItem* renderItem, Vector4 c, double timeAlive);
	//Particula();
	~Particula();

	void integrate(float deltaTime);
	float acumulador;
	//double timeAlive;
};

Particula::Particula(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, Vector4 c = { 0.4,0.3,0.4,1 }, double tA = 5)
{
	position = PxTransform(p.x, p.y, p.z);
	speed = initialSpeed;
	acceleration = a;
	isAlive_ = true;


	renderItem = ri;
	renderItem->transform = &position;
	renderItem->color = c;
	timeAlive = tA;
	damping = d;   //Rozamiento entre 0 y 1
}



inline void Particula::integrate(float deltaTime)
{


	timeAlive -= deltaTime;
	if (timeAlive < 0)isAlive_ = false;

	position.p += (speed * deltaTime);

	this->speed = speed * powf(damping, deltaTime) + acceleration * deltaTime;

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

void Particula::setParticle(Vector3 pos, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, double ta, Vector4 c = { 0.4,0.3,0.4,1 })
{
	position = PxTransform(pos.x, pos.y, pos.z);
	speed = initialSpeed;
	acceleration = a;

	//this->mass = m;

	renderItem = ri;
	renderItem->transform = &position;
	renderItem->color = c;
	timeAlive = ta;

	damping = d;   //Rozamiento entre 0 y 1
}


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