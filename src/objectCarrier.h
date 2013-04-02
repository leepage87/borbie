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
	public:
	irr::scene::ICameraSceneNode *camera;
	irr::scene::ISceneManager *smgr;

  //public:
	ObjectCarrier(irr::scene::ISceneManager *smgr, irr::scene::ICameraSceneNode *camera);
	
	void pickUp(irr::scene::ISceneNode *selected);
	
}; // end of ObjectCarrier class


#endif
