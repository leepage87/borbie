/*	File: map.h
 *	Authors: idk your names
 *
 *	Description: ?
 */

#ifndef MAP_H
#define MAP_H

#include <irrlicht.h>


// VehicleInstance class:
class Map {

  public:
    Map();
    
	irr::scene::ISceneNodeAnimator* getPathTo(irr::scene::ISceneNode *target);
	
	
	
}; // end of Map class


#endif
