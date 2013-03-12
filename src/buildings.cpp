/*	File: buildings.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	buildings list object. The building list object contains a
 *	function for constructing all buildings and placing them into the
 *	scene automatically.
 */

#include "buildings.h"

// include cpp library headers for random number generation
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace irr;
using namespace scene;
using namespace video;


Buildings::Buildings(
	ISceneManager *smgr,
	IVideoDriver *driver,
	IMetaTriangleSelector *metaTriSelector)
{
    // remember pointers to necessary Irrlicht objects
	this->smgr = smgr;
	this->driver = driver;
	this->metaTriSelector = metaTriSelector;
	
	// seed the random number generator (using system time)
	srand(time(NULL));
}

// delete all of the buildings
Buildings::~Buildings(){
	for(std::vector<BuildingInstance *>::iterator it = buildingList.begin();
		it != buildingList.end(); ++it)
	{
		delete (*it);
	}
}


// public addBuilding: add a random building at the given position.
void Buildings::addRandomBuilding(
	float xPos, float yPos, float zPos)
{
    // generate random height
    int rHeight = rand() % 10 + 1;
    rHeight = rHeight * 10 + 50.0;
    
	this->makeBuilding(0, rHeight, xPos, yPos, zPos);
}


// make a building with the given texture and height value
void Buildings::makeBuilding(
    int textureIndex, float height,
	float xPos, float yPos, float zPos)
{
    // create texture, w, h, d based on building type
	ITexture *texture = this->driver->getTexture("assets/textures/building1.png");
	float width = 60.0f;
	float depth = 60.0f;
	
	BuildingInstance *newBuilding
		= new BuildingInstance(
			this->smgr,
			width, height, depth,
			xPos, yPos, zPos,
			texture
		);
	
	newBuilding->applyCollision(this->metaTriSelector);
	
	this->buildingList.push_back(newBuilding);
}
