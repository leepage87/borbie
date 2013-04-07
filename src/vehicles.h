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
#include "vehicleInstance.h"


// types of vehicles
enum VehicleTypes {
	VEHICLE1 = 1
};


// Buildings class:
class Vehicles {

  private:
    // references to the Irrlicht scene objects (to make building nodes)
	irr::scene::ISceneManager *smgr;
	irr::video::IVideoDriver *driver;
	irr::IrrlichtDevice *device;
	irr::scene::IMetaTriangleSelector *metaTriSelector;
	
	// list of vehs
	std::vector<VehicleInstance *> vehicleList;
	
	// list of vehicle models
	std::vector<const char *> modelList;
	
	// vehicle construction functions
	void makeVehicle(int modelIndex, float xPos, float yPos, float zPos);
	
  
  public:
	Vehicles(
		irr::scene::ISceneManager *smgr,
		irr::video::IVideoDriver *driver,
		irr::IrrlichtDevice *device,
		irr::scene::IMetaTriangleSelector *metaTriSelector);
	~Vehicles();
	
	void addRandomVehicle(float xPos, float yPos, float zPos);

	bool isVehicle(irr::scene::ISceneNode* pointer);
	VehicleInstance* getVehicle(irr::scene::ISceneNode* pointer); //returns 0 if not found
	
}; // end of Vehicles class


#endif
