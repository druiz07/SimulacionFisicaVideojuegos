#include "Particula.h"
enum tipoProyectil { PISTOL, ARTILLERY, FIREBALL, TANK, LASER };
class Proyectil :public Particula
{
public:
	Proyectil(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, tipoProyectil currentShotType, double tA, Vector3 pS);
	
};
                           
Proyectil::Proyectil(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, tipoProyectil currentShotType, double tA,Vector3 pS) :Particula(p, initialSpeed, a, m, d, ri, pS,{ 0.4,0.3,0.4,1 },tA)
{
	
	switch (currentShotType)
	{
	case PISTOL:
		setMass(2.0f); // 2.0 Kg
		setVelocity(initialSpeed * 35.0f); // Vsim
		setAcceleration(Vector3{ 0.0f, -1.0f, 0.0f });
		setDamping(0.99f);
		break;
	case ARTILLERY:
		std::cout << "hola";
		setMass(200.0f); // 200.0 Kg
		setVelocity(Vector3{ 0.0f, 30.0f, 40.0f });
		setAcceleration(Vector3{ 0.0f, -20.0f, 0.0f });
		setDamping(0.99f);
		break;
	case FIREBALL:
		setMass(1.0f); // 1.0 Kg
		setVelocity(initialSpeed * 10.0f); // Vsim
		setAcceleration(Vector3{ 0.0f, 0.6f, 0.0f }); // floats
		setDamping(0.9f);
		break;
	case LASER:
		setMass(0.1f); // almost no weight
		setVelocity(initialSpeed * 100); // Vsim
		setAcceleration(Vector3{ 0.0f, 0.0f, 0.0f });
		setDamping(0.99f);
		break;
	case TANK:
		setMass(249457); // Msim
		auto sp = initialSpeed;
		setVelocity(initialSpeed * 100); // Vsim
		setAcceleration(Vector3{ 0.0f, 0.0f, 0.0f });
		setDamping(0.91f);
		break;
	}
	//setParticle(p, initialSpeed, a, m, d, ri);
}
