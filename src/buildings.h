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
    // references to the Irrlicht scene objects (to make building nodes)
	irr::scene::ISceneManager *smgr;
	irr::video::IVideoDriver *driver;
	irr::scene::IMetaTriangleSelector *metaTriSelector;
	
	// list of buildings
	std::vector<BuildingInstance *> buildingList;
	
	// list of building textures
	std::vector<const char *> textureList;
	
	// building construction functions
	void makeBuilding(int textureIndex, float height,
		float xPos, float yPos, float zPos);
	
  
  public:
	Buildings(
		irr::scene::ISceneManager *smgr,
		irr::video::IVideoDriver *driver,
		irr::scene::IMetaTriangleSelector *metaTriSelector);
	~Buildings();
	
	void addRandomBuilding(float xPos, float yPos, float zPos);
	
	
}; // end of Buildings class


#endif
