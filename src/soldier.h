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
	
	public:
	Soldier(
	    GameInstance *gameInstance,
		float posX, float posY, float posZ);

	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		);
	void aim();
	void targetRay();
	bool canShoot();
	void fire();
	void explode();
};
#endif
