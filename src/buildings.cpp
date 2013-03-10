/*	File: buildings.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	buildings list object. The building list object contains a
 *	function for constructing all buildings and placing them into the
 *	scene automatically.
 */

#include "buildings.h"

using namespace irr;
using namespace scene;
using namespace video;


Buildings::Buildings(
	ISceneManager *smgr,
	IVideoDriver *driver,
	IMetaTriangleSelector *metaTriSelector)
{
	this->smgr = smgr;
	this->driver = driver;
	this->metaTriSelector = metaTriSelector;
}

// delete all of the buildings
Buildings::~Buildings(){
	for(std::vector<BuildingInstance *>::iterator it = buildingList.begin();
		it != buildingList.end(); ++it)
	{
		delete (*it);
	}
}


void Buildings::makeBuilding(unsigned int type,
		float xPos, float yPos, float zPos)
{
	// create texture, w, h, d based on building type
	ITexture *texture = this->driver->getTexture("assets/textures/building1.png");
	float width = 100.0f;
	float height = 100.0f;
	float depth = 100.0f;
	
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
