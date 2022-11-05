#pragma once
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
	Vector3 force;
	float inverse_mass;



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
	void clearForce();
	void addForce(const Vector3& f);

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