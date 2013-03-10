/*	File: buildings.h
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	buildings list object. The building list object contains a
 *	function for constructing all buildings and placing them into the
 *	scene automatically.
 */

#ifndef BUILDINGS_H
#define BUILDINGS_H


// include cpp standard library objects
#include <vector>

// include irrlicht
#include <irrlicht.h>

// include building header
#include "buildingInstance.h"


// types of buildings
enum BuildingTypes {
	BUILDING1 = 1
};


// Buildings class:
class Buildings {

  private:
	irr::scene::ISceneManager *smgr;
	irr::video::IVideoDriver *driver;
	irr::scene::IMetaTriangleSelector *metaTriSelector;
	
	std::vector<BuildingInstance *> buildingList;
  
  public:
	Buildings(
		irr::scene::ISceneManager *smgr,
		irr::video::IVideoDriver *driver,
		irr::scene::IMetaTriangleSelector *metaTriSelector);
	~Buildings();
	
	void makeBuilding(unsigned int type,
		float xPos, float yPos, float zPos);
	
	
}; // end of Buildings class


#endif
