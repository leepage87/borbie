/*	File: vehicleInstance.h
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	vehicle instance object. The vehicle object provides a specification
 *	of the abstract GameObject class and contains functions and variables
 *	specific to destructable vehicles placed within the environment.
 */

#ifndef VEHICLE_INSTANCE_H
#define VEHICLE_INSTANCE_H


// include irrlicht
#include <irrlicht.h>

// include obj header
#include "game_object.h"


// define GameInstance to use pointer
class GameInstance;


// VehicleInstance class:
class VehicleInstance : public GameObject {

  public:
	VehicleInstance(
	    GameInstance *gameInstance,
		float posX, float posY, float posZ,
		irr::scene::IAnimatedMesh *mesh, int modelIndex
	);
	
	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		);
	
	
}; // end of Vehicle class


#endif
