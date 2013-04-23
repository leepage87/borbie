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
#include "gameObject.h"


// define GameInstance to use pointer
class GameInstance;


// BuildingInstance class:
class BuildingInstance : public GameObject {

  private:
    // on fire effect particle system
    irr::scene::IParticleSystemSceneNode *fireParticleSystem;
    irr::scene::IParticleSystemSceneNode *sparkParticleSystem;
    bool isOnFire; // whether building is already on fire or not
    
    irr::scene::ISceneNode *roofNode;
    void setAblaze();
    
    // height and Y-position of the building
    float height;
    float posY;
    

  public:
	BuildingInstance(
	    GameInstance *gameInstance,
		float width, float height, float depth,
		float posX, float posY, float posZ,
		irr::video::ITexture *texture,
		irr::video::ITexture *roofTexture
	);
	//~BuildingInstance();
	
	// override to remove the roof and disable fire effects
	virtual void explode();
	
	virtual void applyDamage(int amount);
	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		);
	
	
}; // end of Building class


#endif
