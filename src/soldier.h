#ifndef SOLDIER_H
#define SOLDIER_H

#include <iostream> // TODO: debug (remove)

#include <irrlicht.h>

#include "gameObject.h"
#include "random.h"



// define GameInstance to use pointer
class GameInstance;


class Soldier : public GameObject {
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
    void updatePosition();
    virtual void setMoving();
	virtual void aim();
	virtual bool visible();
	virtual void move();
	virtual bool canShoot();
	virtual void fire();
    virtual bool miss();
};
#endif
