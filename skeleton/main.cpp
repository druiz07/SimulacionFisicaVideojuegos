
#include <ctype.h>
#include <PxPhysicsAPI.h>

#include <vector>
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include <iostream>
#include "Gausiano.hpp"
#include "SistemaParticulas.hpp"
#include "Uniforme.hpp"
#include "ParticleForceRegistry.hpp";
#include "GravityForceGenerator.hpp"
#include "Torbellino.h"
using namespace std;



using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;
std::vector<Proyectil*>	proyectiles;
Particula* diana = NULL;
PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;
ContactReportCallback gContactReportCallback;
SistemaParticulas* Psystem = NULL;
RenderItem* riFloor = NULL;
PxShape* shape;
//ELEMENTOS PRACTICA 3
PxShape* suelo;
ExplosionGenerator* eG;
GravityForceGenerator* g;
VientoGenerator* vG;
Torbellino* tGenerator;
Particula* forceEffects;
float gr;
float k1Wind, k2Wind;
float tForce;
float intensityExplosion;
float radiusExplosion;


void createbaseScene()
{
	Psystem = new  SistemaParticulas();
	suelo = CreateShape(PxBoxGeometry(100, 100, 100));
	


	eG = new ExplosionGenerator();
	intensityExplosion = 10000;
	radiusExplosion = 10;

	eG->setctAnt(intensityExplosion, 3, { 0,0,0 }, radiusExplosion);


	gr = -75;
	k1Wind = 12;
	k2Wind = 0.75;
	tForce = 1;

	g = new GravityForceGenerator({ 0,-10,0 });
	g->setGravity({ 0,gr,0 });
	vG = new VientoGenerator(k1Wind, k2Wind);
	vG->setWindVel({ 10,40,10 }); //Ejemplo para que vaya hacia la derecha

	tGenerator = new Torbellino(1, 0.01, 1, { 0,0,0 });

	forceEffects = new Particula(Vector3{ 0,0,0 }, { 0,0,0 }, Vector3{ 0,0,0 }, 0.2, 0.98, new RenderItem(CreateShape(PxSphereGeometry(200)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.2,0.2,0.5,0 }, 50);
}

void createMainFloor()
{
	riFloor = new RenderItem(CreateShape(PxPlaneGeometry()), Vector4(1, 0, 1, 1));
	PxTransform position = PxTransform(4, 4, 4);

	riFloor->transform = &position;
	riFloor->color = { 0.5,0.5,0.5 ,1 };
}

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);




	Camera* cam = GetCamera();
	cam->getTransform().p = { 60,4,120 };
	//Vector3 dir = cam->getDir();
	//Vector3 pos = cam->getTransform().p;
	//Vector3 dir2{ 0,0,0 };
	//Vector3 pos2 = pos;
	//pos2.z += 100;
	//diana = new Particula(pos + Vector3{ -100,0,-100 }, dir2, { 0.0,0.0,0.0 }, 1, 0.99, new RenderItem(CreateShape(PxSphereGeometry(2.25)), Vector4(1, 0, 1, 1)), Vector4{ 0.5,0.9,0.8,1 },5);
	//Creacion y init de escena

	createMainFloor();
	createbaseScene();
}

// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	//for (int i = 0; i < proyectiles.size(); i++)
	//{
	//	//Actualizacion de fisicas
	//	proyectiles[i]->integrate(t);
	//}
	Psystem->update(t);
	//diana->integrate(t);
	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	for (int i = 0; i < proyectiles.size(); i++)
	{
		delete proyectiles[i];
		//Borrado
	}
	delete diana;
	delete riFloor;
	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	delete forceEffects;


	gFoundation->release();
}


void createExampleExplosion()
{
	Particula* p1 = new Particula(Vector3{ 20,15,0 }, { 0,0,0 }, Vector3{ 0,0,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(3)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.0,0.5,0,1 }, 10);
	Particula* p2 = new Particula(Vector3{ 9,15,15 }, { 0,0,0 }, Vector3{ 0,0,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(3)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.5,0.7,0,3 }, 5);
	Particula* p3 = new Particula(Vector3{ 15,15,10 }, { 0,0,0 }, Vector3{ 0,0,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(3)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.2,0.7,0,4 }, 10);
	Particula* p4 = new Particula(Vector3{ 40,15,0 }, { 0,0,0 }, Vector3{ 0,0,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(3)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.2,0.5,0,1 }, 5);
	Particula* p5 = new Particula(Vector3{ 25,15,30 }, { 0,0,0 }, Vector3{ 0,0,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(3)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.4,0.8,0,1 }, 10);
	Particula* p6 = new Particula(Vector3{ 0,15,15 }, { 0,0,0 }, Vector3{ 0,0,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(3)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.7,0.1,0,2 }, 5);
	Particula* p7 = new Particula(Vector3{ 10,15,5 }, { 0,0,0 }, Vector3{ 0,0,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(3)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.5,0.7,0,5 }, 10);


	Particula* p8 = new Particula(Vector3{ 50,15,0 }, { 0,0,0 }, Vector3{ 0,0,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(3)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.,0.5,0,4 }, 10);
	Particula* p9 = new Particula(Vector3{ 9,15,21 }, { 0,0,0 }, Vector3{ 0,0,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(2)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.9,0.7,0,3 }, 10);
	Particula* p10 = new Particula(Vector3{ 15,17,40 }, { 0,0,0 }, Vector3{ 0,0,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(1)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.2,0.5,0,1 }, 10);
	Particula* p11 = new Particula(Vector3{ 25,15,32 }, { 0,0,0 }, Vector3{ 0,0,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(2)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.2,0,0,8 }, 10);
	Particula* p12 = new Particula(Vector3{ 25,4,30 }, { 0,0,0 }, Vector3{ 0,0,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(1)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.5,0.2,0,1 }, 10);







	eG->setctAnt(intensityExplosion, 2, { 0,0,0 }, radiusExplosion);
	Psystem->addToResgistry(p1, eG);
	Psystem->addToSystem(p1);
	Psystem->addToResgistry(p2, eG);
	Psystem->addToSystem(p2);
	Psystem->addToResgistry(p3, eG);
	Psystem->addToSystem(p3);
	Psystem->addToResgistry(p4, eG);
	Psystem->addToSystem(p4);
	Psystem->addToResgistry(p5, eG);
	Psystem->addToSystem(p5);
	Psystem->addToResgistry(p6, eG);
	Psystem->addToSystem(p6);
	Psystem->addToResgistry(p7, eG);
	Psystem->addToSystem(p7);

	Psystem->addToResgistry(p8, eG);
	Psystem->addToSystem(p8);
	Psystem->addToResgistry(p9, eG);
	Psystem->addToSystem(p9);
	Psystem->addToResgistry(p10, eG);
	Psystem->addToSystem(p10);
	Psystem->addToResgistry(p11, eG);
	Psystem->addToSystem(p11);
	Psystem->addToResgistry(p12, eG);
	Psystem->addToSystem(p12);


}
// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch (toupper(key))
	{

	case 'G':
	{

		gr -= 10;
		g->setGravity({ 0,gr,0 });
		Particula* p = new Particula(Vector3{ 0,0,50 }, { 0,70,0 }, Vector3{ 0,0,0 }, 0.2, 0.98, new RenderItem(CreateShape(PxSphereGeometry(3)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.2,0.2,0.5,1 }, 10);
		g->setGravity({ 0,gr / 2,0 });
		Particula* p1 = new Particula(Vector3{ 10,100,15 }, { 0,0,0 }, Vector3{ 0,0,0 }, 0.2, 0.98, new RenderItem(CreateShape(PxSphereGeometry(3)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.2,0.2,0.5,1 }, 10);
		g->setGravity({ 0,gr / 4,0 });
		Particula* p2 = new Particula(Vector3{ 0,100,25 }, { 0,2,0 }, Vector3{ 0,0,0 }, 0.2, 0.98, new RenderItem(CreateShape(PxSphereGeometry(3)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.2,0.2,0.5,1 }, 10);

		Psystem->addToResgistry(p, g);
		Psystem->addToSystem(p);

		Psystem->addToResgistry(p1, g);
		Psystem->addToSystem(p1);

		Psystem->addToResgistry(p2, g);
		Psystem->addToSystem(p2);


		break;
	}
	case 'V':
	{

		//Viento con direccion a la derecha 

		k1Wind -= 0.8;
		k2Wind -= 0.01;
		vG->setk1k2(k1Wind, k2Wind);

		Particula* p = new Particula(Vector3{ 10,15,0 }, { 0,-30,0 }, Vector3{ 0,0,0 }, 30, 0.98, new RenderItem(CreateShape(PxSphereGeometry(3)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.2,0.2,0.5,1 }, 10);
		Psystem->addToResgistry(p, vG);
		Psystem->addToSystem(p);

		Psystem->genNPart( vG,5);



		break;
	}
	case 'T':
	{

		tForce += 0.1;
		tGenerator->setForce(tForce);
		Particula* p = new Particula(Vector3{ 0,15,0 }, { 5,0,0 }, Vector3{ 0,0,0 }, 0.5, 0.98, new RenderItem(CreateShape(PxSphereGeometry(3)), Vector4(1, 0, 1, 1)), Vector3{ 1000,1000,1000 }, Vector4{ 0.2,0.7,0,1 }, 20);
		Psystem->addToResgistry(p, tGenerator);
		Psystem->addToSystem(p);

		radiusExplosion += 5;
		intensityExplosion *= 5;

		break;
	}
	case 'E':
	{
		Psystem->deleteParticles();
		
		radiusExplosion += 5;
		eG->setRadius(radiusExplosion);

		Psystem->genNPart(eG, 20, false);
		createExampleExplosion();

		break;
	}

	default:
		break;
	}

}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char* const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for (PxU32 i = 0; i < frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}