#ifndef BIG_ASS_SOLDIER_H
#define BIG_ASS_SOLDIER_H


#include <irrlicht.h>
#include "gameObject.h"
#include "audioSystem.h"


// define GameInstance to use pointer
class GameInstance;


class BigAssSoldier : public GameObject {
	private:
	irr::core::line3d<irr::f32> ray;
	unsigned int lastFireTime;
    int fireDelay;
	bool moving;
	irr::f32 length;
    irr::core::vector3df destination;
    SoundClip *bigAssGun;
	
	public:
	BigAssSoldier(
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
    bool miss();
};
#endif
