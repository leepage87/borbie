/*	File: buildingInstance.h
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	building instance object. The building object provides a specification
 *	of the abstract GameObject class and contains functions and variables
 *	specific to destructable buildings placed within the environment.
 */

#ifndef BUILDING_INSTANCE_H
#define BUILDING_INSTANCE_H


// include irrlicht
#include <irrlicht.h>

// include building header
#include "game_object.h"


// BuildingInstance class:
class BuildingInstance : public GameObject {

  public:
	BuildingInstance(
		irr::scene::ISceneManager *smgr,
		irr::video::IVideoDriver *driver,
		float width, float height, float depth,
		float posX, float posY, float posZ,
		irr::video::ITexture *texture
	);
	
	virtual void doDamage(int damage);
	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		);
	
	
}; // end of Building class


#endif
