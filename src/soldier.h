/*********************************************************************
 * File:     soldier.h
 * Authors:  Richard Teammco, Lee Page, Jonathan Miodownik
 * Function: This is the header file for soldier.cpp
 *********************************************************************/
#ifndef SOLDIER_H
#define SOLDIER_H

#include <irrlicht.h>

#include "gameObject.h"
#include "updatable.h"
#include "random.h"



// define GameInstance to use pointer
class GameInstance;


class Soldier : public GameObject, public Updatable {

  protected:
	irr::core::line3d<irr::f32> ray;
	unsigned int lastFireTime;
    int fireDelay;
	bool moving;
    int BULLET_DAMAGE;
    irr::core::vector3df destination;
    
    // per-frame update functions (called via update)
	virtual int lookAtPlayer();
	virtual void aim(int distance);
	virtual void checkMovement(int distance);
	virtual void checkProximity(int distance);
    virtual void setMoving();
    
    // per-frame helper functions
	virtual bool isPlayerVisible();
	
    // per-frame update shoot functions
	virtual bool canShoot();
	virtual void fire(int distance);
    virtual bool miss(int distance);
    virtual int getRandomFireDelay();
	
	// per-frame update movement functions
	virtual void moveToPlayer();
	virtual void aStarToPlayer();
	
  public:
	Soldier(
	    GameInstance *gameInstance,
		float posX, float posY, float posZ);
    
    // override the explosion effect.
    virtual void createExplosionEffect();
    
    // update called each frame by enemy list
    virtual void update();

    // apply collision to this soldier object
	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		);
};
#endif
