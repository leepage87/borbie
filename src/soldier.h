#ifndef SOLDIER_H
#define SOLDIER_H


#include <irrlicht.h>
#include "gameObject.h"


// define GameInstance to use pointer
class GameInstance;


class Soldier : public GameObject {
	private:
	irr::core::line3d<irr::f32> ray;
	unsigned int lastFireTime;
    int fireDelay;
	bool moving;
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
    int  getRandomFireDelay();
    void updatePosition();
    void isMoving();
	void aim();
	void targetRay();
	void move();
	bool canShoot();
	void fire();
};
#endif
