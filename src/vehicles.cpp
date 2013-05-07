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

const unsigned int MAX_NUMBER_VEHICLES = 30;
const unsigned int SPAWN_TIME_MS = 3 * 1000; // 3 seconds
const unsigned int ROAD_HEIGHT = 30;


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
	
	this->nextSpawnTime = 0;
}


// Generates the initial batch of vehicles randomly between two road intersections,
//  and assigns them to go towards one of them. The number of vehicles generated
//  is however many maximum number of vehicles are allowed for this map.
void Vehicles::generateObjects(){
    MapReader *mapReader = this->gameInstance->getMapReader();
    int numRoadIntersections = mapReader->roadIntersectionCoords.size();
    
    for(int i=0; i<MAX_NUMBER_VEHICLES; i++){
        // TODO - does not check for accidental "island" nodes, which should
        //  not exist anyway and MapReader should check for those.
        
        // get first intersection randomly
        int rand = Random::randomInt(numRoadIntersections);
        RoadIntersection first = mapReader->roadIntersectionCoords[rand];
        
        // get second intersection randomly
        rand = Random::randomInt(first.connections.size());
        RoadIntersection *second = first.connections[rand];
        
        // randomly find a position between the two intersections
        float pos = Random::randomFloat();
        float vehicleX = first.X + (pos * (second->X - first.X));
        float vehicleY = first.Y + (pos * (second->Y - first.Y));
        
        // add the vehicle to the map
        VehicleInstance *vehicle = this->addRandomVehicle(
            vehicleX,
            ROAD_HEIGHT,
            vehicleY);
        
        // make the vehicle move towards the second intersection
        vehicle->setNextIntersection(second);
        vehicle->go();
    }
}


// Called each frame to update all of the vehicles in the world, and check if
//  it's time to spawn a new vehicle.
void Vehicles::update(){
    // update all vehicles
    for(std::vector<GameObject *>::iterator it = this->objList.begin();
	    it != this->objList.end(); ++it)
	{
		((VehicleInstance *)(*it))->update();
	}
	
	// if spawn timer is ready, and there aren't too many vehicles in the
	//  world, create a new vehicle at a random spawn point.
	if( this->gameInstance->currentGameTime >= this->nextSpawnTime &&
	    this->objList.size() < MAX_NUMBER_VEHICLES)
	{
	    this->spawnRandomVehicle();
	    this->nextSpawnTime = this->gameInstance->currentGameTime + SPAWN_TIME_MS;
	}
}


// Spawn a vehicle into the world using a SpawnPoint from the MapReader.
//  If the MapReader has no spawn points, does nothing. Vehicle type is
//  is completely randomized.
void Vehicles::spawnRandomVehicle(){
    MapReader *mapReader = this->gameInstance->getMapReader();
    
    // choose a random spawn point
    int numSpawnPoints = mapReader->vehicleSpawnPoints.size();
    if(numSpawnPoints == 0)
        return; // if no spawn points, can't do anything, so return.
    int spawnPointIndex = Random::randomInt(numSpawnPoints);
    RoadSpawnPoint spawnPoint = mapReader->vehicleSpawnPoints[spawnPointIndex];
    VehicleInstance *spawnedVehicle = this->addRandomVehicle(
        spawnPoint.X,
        ROAD_HEIGHT,
        spawnPoint.Y );
    
    // make newly spawned vehicle move to the first intersection connected to
    //  its spawn point.
    spawnedVehicle->setNextIntersection(spawnPoint.connection);
    spawnedVehicle->go();
}


// public addRandomVehicle: add a random vehicle at the given position.
VehicleInstance* Vehicles::addRandomVehicle(
	float xPos, float yPos, float zPos)
{
    //std::cout << "RANDOM VEHICLE CREATED AT: " << xPos << ", " << zPos << std::endl;
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
	// TODO - if you don't drop this, is it a memory leak?

    // create the new vehicle, add collision to it, and add it to the list
	VehicleInstance *newVehicle
		= new VehicleInstance(
			this->gameInstance,
			xPos, yPos, zPos, mesh, modelIndex
		);
	newVehicle->applyCollision(this->metaTriSelector);
	this->addObject(newVehicle);
	
	return newVehicle;
}
