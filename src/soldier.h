#ifndef SOLDIER_H
#define SOLDIER_H

#include <iostream> // TODO: debug (remove)

#include <irrlicht.h>

#include "gameObject.h"
#include "audioSystem.h"
#include "random.h"


// define GameInstance to use pointer
class GameInstance;


class Soldier : public GameObject {
	private:
	irr::core::line3d<irr::f32> ray;
	unsigned int lastFireTime;
    int fireDelay;
	bool moving;
    int BULLET_DAMAGE;
	irr::f32 length;
    irr::core::vector3df destination;
    SoundClip *burst;
	
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
    void setMoving();
	void aim();
	bool visible();
	void move();
	bool canShoot();
	void fire();
    bool miss();
};
#endif
