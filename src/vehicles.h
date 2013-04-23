/*	File: buildings.h
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	buildings list object. The building list object contains a
 *	function for constructing all buildings and placing them into the
 *	scene automatically.
 */

#ifndef VEHICLES_H
#define VEHICLES_H


// include cpp standard library objects
#include <vector>

// include irrlicht
#include <irrlicht.h>

// include building header
#include "objectList.h"
#include "vehicleInstance.h"


// declare GameInstance to use its pointer
class GameInstance;


// types of vehicles
enum VehicleTypes {
	VEHICLE1 = 1
};


// Buildings class:
class Vehicles : public ObjectList {

  private:
    // list of vehicle models
	std::vector<const char *> modelList;
	
	// vehicle construction functions
	VehicleInstance* makeVehicle(int modelIndex, float xPos, float yPos, float zPos);
	
	// virtual game time indicating when to spawn the next vehicle.
	unsigned int nextSpawnTime;
	
  
  public:
	Vehicles(
		irr::scene::IMetaTriangleSelector *metaTriSelector,
		GameInstance *gameInstance);
	
	VehicleInstance* addRandomVehicle(float xPos, float yPos, float zPos);
	
	// Updates all vehicles to keep on moving, and also spawns vehicles at
	//  appropriate times.
	void update();
	
	// Randomly spawns a vehicle into the world using a Map spawnpoint.
	void spawnRandomVehicle(); // TODO - make private
	
	
}; // end of Vehicles class


#endif
