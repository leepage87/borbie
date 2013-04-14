/*
 */
#ifndef ENEMY_H
#define ENEMY_H


#include <irrlicht.h>
#include "game_object.h"


// define GameInstance to use pointer
class GameInstance;


// Enemy class: abstract, extends GameObject
class Enemy : public GameObject {
	protected:
	irr::scene::IAnimatedMeshSceneNode *sceneNode;
	public:
	Enemy (irr::scene::ISceneManager *smgr,
				irr::video::IVideoDriver *driver,
				irr::IrrlichtDevice *device,
				GameInstance *gameInstance);

	virtual void doDamage(int damage);

	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		);
}; // end of Enemy class


#endif
