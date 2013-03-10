/*	File: building.h
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration of the
 *	building object. The building object provides a specification
 *	of the abstract GameObject class and contains functions and variables
 *	specific to destructable buildings placed within the environment.
 */

#ifndef BUILDING_H
#define BUILDING_H


// include irrlicht
#include <irrlicht.h>

// include building header
#include "game_object.h"


// Building class:
class Building : public GameObject {

  public:
	Building(
		irr::scene::ISceneManager *smgr,
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
