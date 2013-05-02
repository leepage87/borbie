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
	bool moving;
	irr::f32 length;
	
	public:
	Soldier(
	    GameInstance *gameInstance,
		float posX, float posY, float posZ);
    
    // override the explosion effect.
    virtual void createExplosionEffect();

	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		);
	void aim();
	void targetRay();
	void move();
	bool canShoot();
	void fire();
};
#endif
