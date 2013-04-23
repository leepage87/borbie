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
#include "mapReader.h"
#include "random.h"

using namespace irr;
using namespace scene;
using namespace video;

#include <iostream>


Vehicles::Vehicles(
	IMetaTriangleSelector *metaTriSelector,
	GameInstance *gameInstance)
	//passing these to supah constructah:
	: ObjectList(metaTriSelector, gameInstance)
{
	// populate the model list
	//this->modelList.push_back("assets/models/vehicles/eclipse/2003eclipse.obj");
	//this->modelList.push_back("assets/models/vehicles/h2/h2.3ds");
	this->modelList.push_back("assets/models/vehicles/jeep/jeep.obj");
	//this->modelList.push_back("assets/models/vehicles/corradon/car2.obj");
	//this->modelList.push_back("assets/models/vehicles/pigMobile/PoliceCar.3DS");
	//this->modelList.push_back("assets/models/vehicles/lambo/Lamborghini.x");
	this->modelList.push_back("assets/models/vehicles/riviera/car_riviera.obj");
}


void Vehicles::update(){
    // update all vehicles
    for(std::vector<GameObject *>::iterator it = this->objList.begin();
	    it != this->objList.end(); ++it)
	{
		((VehicleInstance *)(*it))->updateMovement();
	}
	
	// if spawn timer is ready, create a new vehicle TODO
}


// Spawn a vehicle into the world using a SpawnPoint from the MapReader.
//  If the MapReader has no spawn points, does nothing. Vehicle type is
//  is completely randomized.
void Vehicles::spawnRandomVehicle(){
    int numSpawnPoints = MapReader::vehicleSpawnPoints.size();
    if(numSpawnPoints == 0)
        return;
    
    // choose a random spawn point
    int spawnPointIndex = Random::randomInt(numSpawnPoints);
    RoadSpawnPoint spawnPoint = MapReader::vehicleSpawnPoints[spawnPointIndex];
    VehicleInstance *spawnedVehicle = this->addRandomVehicle(
        spawnPoint.X,
        120, //70, // road height
        spawnPoint.Y );
    
    spawnedVehicle->setNextIntersection(spawnPoint.connection);
    spawnedVehicle->go();
}


// public addRandomVehicle: add a random vehicle at the given position.
VehicleInstance* Vehicles::addRandomVehicle(
	float xPos, float yPos, float zPos)
{
    std::cout << "RANDOM VEHICLE CREATED AT: " << xPos << ", " << zPos << std::endl;
    // get a random index from the model list
    int modelIndex = Random::randomInt(this->modelList.size());
    
	return this->makeVehicle(modelIndex, xPos, yPos, zPos);
}

// make a vehicle with the given texture and height value
VehicleInstance* Vehicles::makeVehicle(int modelIndex,
	float xPos, float yPos, float zPos)
{
    // get the vehicle mesh
	IAnimatedMesh *mesh =
	    smgr->getMesh(this->modelList[modelIndex]);


	VehicleInstance *newVehicle
		= new VehicleInstance(
			this->gameInstance,
			xPos, yPos, zPos, mesh, modelIndex
		);
	
	newVehicle->applyCollision(this->metaTriSelector);
	
	this->addObject(newVehicle);
	
	return newVehicle;
}
