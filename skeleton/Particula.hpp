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
	Vector3 actionSpace;

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
	bool checkSpace();
	virtual Particula* clone(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, Vector3 posSpace, Vector4 c = { 0.4,0.3,0.4,1 }, double tA = 5);

	bool isAlive();
	void setParticle(Vector3 pos, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, Vector3 posSpace, double timeAlive, Vector4 color);

	Vector3 getPosition() const;
	float getMass() const;
	Vector3 getVelocity() const;
	Vector3 getAcceleration() const;

	float getDamping() const;

	Particula(Vector3 position, Vector3 initialSpeed, Vector3 acceleration, float mass, float damping, RenderItem* renderItem, Vector3 posSpace, Vector4 c, double timeAliv);
	//Particula();
	~Particula();

	void integrate(float deltaTime);
	float acumulador;
	//double timeAlive;
};

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

inline bool Particula::checkSpace()
{
	if (position.p.x > actionSpace.x || position.p.y > actionSpace.y || position.p.z > actionSpace.z)return false;
	else if (position.p.x < -actionSpace.x || position.p.y < -actionSpace.y || position.p.z < -actionSpace.z)return false;;
	return true;

}

inline Particula* Particula::clone(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, Vector3 posSpace, Vector4 c = { 0.4,0.3,0.4,1 }, double tA = 5)
{
	return new Particula(p,  initialSpeed,  a,  m,  d,   ri,  posSpace,  c = { 0.4,0.3,0.4,1 },  tA = 5);
}

void Particula::setParticle(Vector3 pos, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, Vector3 posSpace, double ta, Vector4 c = { 0.4,0.3,0.4,1 })
{
	position = PxTransform(pos.x, pos.y, pos.z);
	speed = initialSpeed;
	acceleration = a;

	//this->mass = m;

	renderItem = ri;
	renderItem->transform = &position;
	renderItem->color = c;
	timeAlive = ta;
	actionSpace = posSpace;

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