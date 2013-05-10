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
	irr::f32 length;
    irr::core::vector3df destination;
	
	public:
	Soldier(
	    GameInstance *gameInstance,
		float posX, float posY, float posZ);
    
    // override the explosion effect.
    virtual void createExplosionEffect();

	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		);
    virtual int  getRandomFireDelay();
    virtual void update();
    virtual void setMoving();
	virtual void aim();
	virtual bool visible();
	virtual void move();
	virtual void goToBorbie();
	virtual bool canShoot();
	virtual void fire(int distance);
    virtual bool miss(int distance);
};
#endif
