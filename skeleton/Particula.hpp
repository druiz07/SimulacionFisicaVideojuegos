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
	Particula(Vector3 position, Vector3 initialSpeed, Vector3 acceleration, float mass, float damping, RenderItem* renderItem);
	~Particula();

	void PhysicUpdate(float deltaTime);
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



inline void Particula::PhysicUpdate(float deltaTime)
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

Particula::~Particula()
{
	DeregisterRenderItem(this->renderItem);
}