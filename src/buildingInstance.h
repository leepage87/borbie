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

  private:
    // on fire effect particle system
    irr::scene::IParticleSystemSceneNode *fireParticleSystem;
    irr::scene::IParticleSystemSceneNode *sparkParticleSystem;
    
    // height and Y-position of the building
    float height;
    float posY;
    

  public:
    void setAblaze();
	BuildingInstance(
		irr::scene::ISceneManager *smgr,
		irr::video::IVideoDriver *driver,
	    irr::IrrlichtDevice *device,
		float width, float height, float depth,
		float posX, float posY, float posZ,
		irr::video::ITexture *texture,
		irr::video::ITexture *roofTexture
	);
	~BuildingInstance();
	
	virtual void doDamage(int damage);
	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		);
	
	
}; // end of Building class


#endif
