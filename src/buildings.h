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
#include "objectList.h"


// building constants:
#define BUILDING_GROUND_HEIGHT 0.0f
#define BUILDING_WIDTH 40.0f
#define BUILDING_DEPTH 40.0f
// height max and min values:
#define BUILDING_MIN_HEIGHT 25
#define BUILDING_MAX_HEIGHT 75
// minimum difference between building heights:
#define BUILDING_HEIGHT_DIFF 5
// random building height bias (1+):
#define BUILDING_HEIGHT_BIAS 2 // larger => more biased to average height


// declare GameInstance to use its pointer
class GameInstance;


// types of buildings
enum BuildingTypes {
	BUILDING1 = 1
};


// Buildings class:
class Buildings : public ObjectList {

  private:
	// list of building textures
	std::vector<const char *> textureList;
	
	// random height generator function (restricted to a certain height range,
	//  and bias towards mid-ranged heights)
    float getRandomHeight();
	
	// building construction functions
	BuildingInstance* makeBuilding(int textureIndex, int roofTexture, float height,
		float xPos, float yPos, float zPos);
	
  
  public:
    // constructor/destructor
	Buildings(
		irr::scene::IMetaTriangleSelector *metaTriSelector,
		GameInstance *gameInstance);

	
	// build the city using the given building coordinates file path
	void generateBuildings(const char *buildingCoords);
	
	// add a randomly sized and textured building to the scene, returning the
	//	pointer to the newly created building object
	BuildingInstance* addRandomBuilding(float xPos, float yPos, float zPos);
	
	
}; // end of Buildings class


#endif
