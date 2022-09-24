#include "Particula.hpp"
enum tipoProyectil { PISTOL, ARTILLERY, FIREBALL, TANK, LASER };
class Proyectil :Particula
{
public:
	Proyectil(Vector3 position, Vector3 initialSpeed, Vector3 acceleration, float mass, float damping, RenderItem* renderItem, tipoProyectil currentShotType);
	void setParticle(Vector3 position, Vector3 initialSpeed, Vector3 acceleration, float mass, float damping, RenderItem* renderItem);

};
Proyectil::Proyectil(Vector3 position, Vector3 initialSpeed, Vector3 acceleration, float mass, float damping, RenderItem* renderItem,tipoProyectil currentShotType)
{
	setParticle(position , initialSpeed, acceleration,mass,damping,renderItem);
	switch (currentShotType)
	{
	case PISTOL:
		setMass(2.0f); // 2.0 Kg
		setVelocity(Vector3{ 0.0f, 0.0f, 35.0f }); // 35 m/s
		setAcceleration(Vector3{ 0.0f, -1.0f, 0.0f });
		setDamping(0.99f);
		break;
	case ARTILLERY:
		setMass(200.0f); // 200.0 Kg
		setVelocity(Vector3{ 0.0f, 30.0f, 40.0f });
		setAcceleration(Vector3{ 0.0f, -20.0f, 0.0f });
		setDamping(0.99f);
		break;
	case FIREBALL:
		setMass(1.0f); // 1.0 Kg
		setVelocity(Vector3{ 0.0f, 0.0f, 10.0f });
		setAcceleration(Vector3{ 0.0f, 0.6f, 0.0f }); // floats
		setDamping(0.9f);
		break;
	case LASER:
		setMass(0.1f); // almost no weight
		setVelocity(Vector3{ 0.0f, 0.0f, 100.0f }); // No gravity
		setAcceleration(Vector3{ 0.0f, 0.0f, 0.0f });
		setDamping(0.99f);
		break;
	case TANK:
		setMass(249457); // Msim
		setVelocity(Vector3{ 75.0f, 0.0f, 100.0f }); // Vsim
		setAcceleration(Vector3{ 0.0f, 0.0f, 0.0f });
		setDamping(0.99f);
		break;
	}
}
void Proyectil::setParticle(Vector3 position, Vector3 initialSpeed, Vector3 acceleration, float mass, float damping, RenderItem* renderItem)
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