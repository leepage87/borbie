/*	File: ObjectCarrier.h
 *	Authors: teamKillYourself
 *
 *	Description: this file contains the class declaration of the
 *	object carrier, which allows the user to pickup and throw objects
 */

#ifndef CARRY_OBJECT_H
#define CARRY_OBJECT_H


// include irrlicht
#include <irrlicht.h>


// ObjectCarrier class:
class ObjectCarrier {
  private:
	irr::scene::ICameraSceneNode *camera;
	irr::scene::ISceneManager *smgr;
	irr::scene::ISceneNode *selected;

    // timer values: count time since an object was thrown
	irr::ITimer *timer;
    unsigned int timerStopTime;
    
    
  public:
    // constructor: keep track of Irrlicht object pointers
	ObjectCarrier(irr::scene::ISceneManager *smgr,
	              irr::IrrlichtDevice *device,
	              irr::scene::ICameraSceneNode *camera);
	
	// "pick up", or keep track of, the given scene node
	void pickUp(irr::scene::ISceneNode *selected);
	
	// throw the object: set the target destination and throw it
	//irr::core::vector3df throwObj(irr::scene::ISceneNode *target);
	void throwObj(irr::scene::ISceneNode *target);
	
	// returns TRUE if the last object recently thrown has been flying
	//  for the pre-determined constant amount of flight-time.
	bool objectDoneFlying();
	
}; // end of ObjectCarrier class


#endif
