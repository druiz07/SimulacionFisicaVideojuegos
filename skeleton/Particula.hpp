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

	float mass, damping;
	RenderItem* renderItem;

	Particula() noexcept;
	void setPosition(Vector3 position);
	void setMass(float mass);
	void setVelocity(Vector3 s);
	void setAcceleration(Vector3 a);
	void setDamping(float d);
	void setColor(Vector4 color);
	void setSize(const float size);
	void setColorShiftSpeed(const float shiftSpeed);
	void setParticle(Vector3 pos, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri);

	Vector3 getPosition() const;
	float getMass() const;
	Vector3 getVelocity() const;
	Vector3 getAcceleration() const;
	float getDamping() const;

	Particula(Vector3 position, Vector3 initialSpeed, Vector3 acceleration, float mass, float damping, RenderItem* renderItem);
	//Particula();
	~Particula();

	void integrate(float deltaTime);
	float acumulador;
};

Particula::Particula(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri)
{
	position = PxTransform(p.x, p.y, p.z);
	speed = initialSpeed;
	acceleration = a;

	//this->mass = m;

	renderItem = ri;
	renderItem->transform = &position;
	renderItem->color = Vector4{ 0.4,0.3,0.4,1 };

	damping = d;   //Rozamiento entre 0 y 1
}



inline void Particula::integrate(float deltaTime)
{
	position.p += (speed * deltaTime);
	//this->speed += (this->acceleration * deltaTime);

	this->speed = speed *powf(damping, deltaTime) + acceleration * deltaTime;
}

//Particula::Particula() 
//{
//	position = PxTransform(0, 0, 0);
//	speed = { 1,0,0 };
//	acceleration = { 0,0,0 };
//	mass = 0;
//	renderItem = new RenderItem(CreateShape(PxSphereGeometry(2.0)), &position, Vector4(1, 0, 1, 1));
//	damping = 0;
//}


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

inline void Particula::setParticle(Vector3 pos, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri)
{
	position = PxTransform(pos.x, pos.y, pos.z);
	speed = initialSpeed;
	acceleration = a;

	//this->mass = m;

	renderItem = ri;
	renderItem->transform = &position;
	renderItem->color = Vector4{ 0.4,0.3,0.4,1 };

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