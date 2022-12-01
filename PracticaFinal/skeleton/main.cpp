#include <ctype.h>
#include <PxPhysicsAPI.h>
#include <vector>
#include <list>
#include <iostream>
#include <climits>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "SceneManager.h"
#include "SistemasScene.h"
#include "MuelleAncladoScene.h"
#include "ParticulasUnidasScene.h"
#include "MuelleFlotadorScene.h"
#include "SolidosRigidosScene.h"

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

SceneManager* sceneManager = NULL;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

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
	// ------------------------------------------------------

	sceneManager = new SceneManager(new SistemasScene(), SceneNames::SISTEMAS);
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	sceneManager->getCurrentScene()->update(t);

	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	gFoundation->release();

	delete sceneManager;
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	if (key < 48 || key > 57) sceneManager->getCurrentScene()->keyPress(toupper(key));
	else {
		auto n = (SceneNames)(key - '0');

		switch (key - '0')
		{
		case (int)SceneNames::SISTEMAS: {
			sceneManager->loadScene(new SistemasScene(), n);
			break;
		}
		case (int)SceneNames::MUELLE_ANCLADO: {
			sceneManager->loadScene(new MuelleAncladoScene(), n);
			break;
		}
		case (int)SceneNames::PARTICULAS_UNIDAS: {
			sceneManager->loadScene(new ParticulasUnidasScene(), n);
			break;
		}
		case (int)SceneNames::MUELLE_FLOTADOR: {
			sceneManager->loadScene(new MuelleFlotadorScene(), n);
			break;
		}
		case (int)SceneNames::SOLIDOS_RIGIDOS: {
			sceneManager->loadScene(new SolidosRigidosScene(gScene, gPhysics), n);
			break;
		}
		default:
			std::cout << "Numero de escena no valido!\n";
			break;
		}
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) {
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}

int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}
