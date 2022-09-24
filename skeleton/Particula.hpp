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
	void setVelocity(Vector3 speed);
	void setAcceleration(Vector3 acceleration);
	void setDamping(float damping);
	void setColor(Vector4 color);
	void setSize(const float size);
	void setColorShiftSpeed(const float shiftSpeed);

	Vector3 getPosition() const;
	float getMass() const;
	Vector3 getVelocity() const;
	Vector3 getAcceleration() const;
	float getDamping() const;

	Particula(Vector3 position, Vector3 initialSpeed, Vector3 acceleration, float mass, float damping, RenderItem* renderItem);
	~Particula();

	void integrate(float deltaTime);
	float acumulador;
};

Particula::Particula(Vector3 position, Vector3 initialSpeed, Vector3 acceleration, float mass, float damping, RenderItem* renderItem)
{
	this->position = PxTransform(position.x, position.y, position.z);
	this->speed = initialSpeed;
	this->acceleration = acceleration;

	//this->mass = mass;

	this->renderItem = renderItem;
	this->renderItem->transform = &this->position;
	this->renderItem->color = Vector4{ 0.4,0.3,0.4,1 };

	this->damping = damping;   //Rozamiento entre 0 y 1
}



inline void Particula::integrate(float deltaTime)
{
	this->position.p += (this->speed * deltaTime);
	//this->speed += (this->acceleration * deltaTime);

	this->speed = this->speed*  powf(damping, deltaTime) + acceleration * deltaTime;
}

Particula::Particula() noexcept
{
	this->position = PxTransform(0, 0, 0);
	this->speed = { 1,0,0 };
	this->acceleration = { 0,0,0 };
	this->mass = 0;
	this->renderItem = new RenderItem(CreateShape(PxSphereGeometry(2.0)), &position, Vector4(1, 0, 1, 1));
	this->damping = 0;
}


void Particula::setPosition(Vector3 position)
{
	this->position.p = position;
}

void Particula::setMass(float mass)
{
	this->mass = mass;
}

void Particula::setVelocity(Vector3 speed)
{
	this->speed = speed;
}

void Particula::setAcceleration(Vector3 acceleration)
{
	this->acceleration = acceleration;
}

void Particula::setDamping(float damping)
{
	this->damping = damping;
}

void Particula::setColor(Vector4 color)
{
	this->renderItem->color = color;
}

void Particula::setSize(const float size)
{
	renderItem->shape = CreateShape(PxSphereGeometry(size));
}


Vector3 Particula::getPosition() const
{
	return this->position.p;
}

float Particula::getMass() const
{
	return this->mass;
}

Vector3 Particula::getVelocity() const
{
	return this->speed;
}

Vector3 Particula::getAcceleration() const
{
	return this->acceleration;
}

float Particula::getDamping() const
{
	return this->damping;
}

Particula::~Particula()
{
	DeregisterRenderItem(this->renderItem);
}