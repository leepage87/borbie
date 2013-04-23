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
#include "gameObject.h"
#include "mapReader.h"


// define GameInstance to use pointer
class GameInstance;


// VehicleInstance class:
class VehicleInstance : public GameObject {

  private:
    // location of the next intersection to go to
    RoadIntersection *lastIntersection;
    RoadIntersection *nextIntersection;
    
    // Animator animating movement
    irr::scene::ISceneNodeAnimator *motionAnimator;
    

  public:
	VehicleInstance(
	    GameInstance *gameInstance,
		float posX, float posY, float posZ,
		irr::scene::IAnimatedMesh *mesh, int modelIndex
	);
	
	~VehicleInstance();
	
	
	// World movement functions:
	
	// Set the next intersection of this vehicle.
	void setNextIntersection(RoadIntersection *nextIntersection);
	
	// Start moving towards the next intersection.
	void go();
	
	// Stops moving and removes all animators.
	void stop();
	
	// Updates animator checks. If animation done, selects next random
	//  position to go to.
	void updateMovement();
	
	
	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		);
	
	
}; // end of Vehicle class


#endif
