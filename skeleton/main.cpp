
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


void createbaseScene()
{
	//GeneradorGaussiano* gGauss = new GeneradorGaussiano({ 0.2,0.1,0.1 }, { .1,.1,.1 }, "Gaussiano1", { 25,40,0 }, { 2,25,0 }, { 0.1,0.2,0.7,1 }, 1, 6);
	//Uniforme* uniform = new Uniforme({ 0.2,0.1,0.1 }, { .1,.1,.1 }, { 10,10,0 }, { 20,20,2 }, "Uniforme", { 1,1,10 }, { 2,20,0 }, { 0.5,0.2,0.7,1 }, 1, 6, 50, { 15,70,10 },800);
	//Uniforme* uniform2 = new Uniforme({ 0.5,0.2,0.1 }, { .1,.1,.1 }, { 40,10,0 }, { 20,20,2 }, "Uniforme2", { 1,1,10 }, { 5,20,0 }, { 0.2,0.7,0.7,1 }, 1, 6, 50, { 15,70,10 },800);
	Psystem = new SistemaParticulas();
	//Psystem->addGen(uniform);
	//Psystem->addGen(uniform2);
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

	//Camera* cam = GetCamera();
	//Vector3 dir = cam->getDir();
	//Vector3 pos = cam->getTransform().p;
	//Vector3 dir2{ 0,0,0 };
	//Vector3 pos2 = pos;
	//pos2.z += 100;
	//diana = new Particula(pos + Vector3{ -100,0,-100 }, dir2, { 0.0,0.0,0.0 }, 1, 0.99, new RenderItem(CreateShape(PxSphereGeometry(2.25)), Vector4(1, 0, 1, 1)), Vector4{ 0.5,0.9,0.8,1 },5);
	//Creacion y init de escena

	 
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

	gFoundation->release();
}
void createMainFloor()
{
	riFloor = new RenderItem(CreateShape(PxPlaneGeometry()), Vector4(1, 0, 1, 1));
	PxTransform position = PxTransform(4, 4, 4);

	riFloor->transform = &position;
	riFloor->color = { 0.5,0.5,0.5 ,1 };
}
// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch (toupper(key))
	{
		
	case 'T':
	{
		createMainFloor();
		/*
		Camera* cam = GetCamera();
		Vector3 dir = cam->getDir();
		Vector3 pos = cam->getTransform().p;
		Vector3 dir2{ 0,0,0 };
		Vector3 pos2=pos;*/

		createMainFloor();
		Psystem->generateFireworkSistem(Vector3{ 0,0,15 }, { 0,30,0 }, Vector3{ 0,-10,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(2)), Vector4(1, 0, 1, 1)), 1.5, 3, Vector4{ 0.2,0.2,0.5,1 }, 4, 10);
		Psystem->generateFireworkSistem(Vector3{ 0,0,25 }, { 0,15,0 }, Vector3{ 0,-10,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(2.5)), Vector4(1, 0, 1, 1)), 1.5, 4, Vector4{ 0.7,0.9,0.1,1 }, 4, 10);		
		break;
	}
	case 'H':
	{

		Psystem->generateFireworkSistem(Vector3{ 5,0,5 }, { 0,25,0 }, Vector3{ 0,-10,0 }, 90, 0.98, new RenderItem(CreateShape(PxSphereGeometry(2)), Vector4(1, 0, 1, 1)), 1.5, 2, Vector4{ 0.7,0.9,0.1,1 }, 5, 20,"circulo3d");
		//Psystem->generateFireworkSistem(Vector3{ 5,0,5 }, { 0,40,0 }, Vector3{ 0,-10,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(1)), Vector4(1, 0, 1, 1)), 1.5, 2, Vector4{ 0.2,0.9,0.2,1 }, 5, 20, "lineas");
		break;
	}
	case'K':
	{
	
		Psystem->generateFireworkSistem(Vector3{ 5,0,5 }, { 0,25,0 }, Vector3{ 0,-5,0 }, 30, 0.98, new RenderItem(CreateShape(PxSphereGeometry(2)), Vector4(1, 0, 1, 1)), 1.5, 2, Vector4{ 0.7,0.9,0.1,1 }, 5, 20, "circulo");
		break;
	}
	case 'O':
	{
		Psystem->generateFireworkSistem(Vector3{ 0,0,15 }, { 0,30,0 }, Vector3{ 0,-7,0 }, 1, 0.98, new RenderItem(CreateShape(PxSphereGeometry(2)), Vector4(1, 0, 1, 1)), 1.5, 2, Vector4{ 0.2,0.2,0.5,1 }, 5, 15, "lineas");
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