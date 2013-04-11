/*
 */
#ifndef ENEMY_H
#define ENEMY_H


#include <irrlicht.h>
#include "game_object.h"


// Enemy class: abstract, extends GameObject
class Enemy : public GameObject {
	protected:
	irr::scene::IAnimatedMeshSceneNode *sceneNode;
	public:
	Enemy (irr::scene::ISceneManager *smgr,
				irr::video::IVideoDriver *driver,
				irr::IrrlichtDevice *device);

	virtual void doDamage(int damage);

	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		);
}; // end of Enemy class


#endif
