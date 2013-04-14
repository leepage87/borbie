/*	File: vehicles.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	vehicles list object. The vehicles list object contains a
 *	function for constructing all vehicles and placing them into the
 *	scene automatically.
 */

#include "vehicles.h"
#include "gameInstance.h"

// include cpp library headers for random number generation
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace irr;
using namespace scene;
using namespace video;

#include <iostream>


Vehicles::Vehicles(
	ISceneManager *smgr,
	IVideoDriver *driver,
	IrrlichtDevice *device,
	IMetaTriangleSelector *metaTriSelector,
	GameInstance *gameInstance)
	//passing these to supah constructah:
	: ObjectList(smgr, driver, device, metaTriSelector, gameInstance)
{
    // seed the random number generator (using system time)
	srand(time(NULL)); // TODO - do this elsewhere
	
	// populate the model list
	//this->modelList.push_back("assets/models/vehicles/eclipse/2003eclipse.obj");
	//this->modelList.push_back("assets/models/vehicles/h2/h2.3ds");
	this->modelList.push_back("assets/models/vehicles/jeep/jeep.obj");
	//this->modelList.push_back("assets/models/vehicles/corradon/car2.obj");
	//this->modelList.push_back("assets/models/vehicles/pigMobile/PoliceCar.3DS");
	//this->modelList.push_back("assets/models/vehicles/lambo/Lamborghini.x");
	this->modelList.push_back("assets/models/vehicles/riviera/car_riviera.obj");
}


// public addRandomVehicle: add a random vehicle at the given position.
void Vehicles::addRandomVehicle(
	float xPos, float yPos, float zPos)
{
    // get a random index from the model list
    int modelIndex = rand() % this->modelList.size();
    
	this->makeVehicle(modelIndex, xPos, yPos, zPos);
}

// make a vehicle with the given texture and height value
void Vehicles::makeVehicle(int modelIndex,
	float xPos, float yPos, float zPos)
{
    // get the vehicle mesh
	IAnimatedMesh *mesh =
	    smgr->getMesh(this->modelList[modelIndex]);


	VehicleInstance *newVehicle
		= new VehicleInstance(
			this->smgr, this->driver, this->device, this->gameInstance,
			xPos, yPos, zPos, mesh, modelIndex
		);
	
	newVehicle->applyCollision(this->metaTriSelector);
	
	this->addObject(newVehicle);
}
