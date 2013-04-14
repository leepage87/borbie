/*
 */
#ifndef ENEMY_H
#define ENEMY_H


#include <irrlicht.h>
#include "objectList.h"
#include "soldier.h"



// Enemy class: abstract, extends GameObject
class Enemy : public ObjectList {
	
	public:
	Enemy (irr::scene::ISceneManager *smgr,
			irr::video::IVideoDriver *driver,
			irr::IrrlichtDevice *device, 
			irr::scene::IMetaTriangleSelector *metaTriSelector);
	void makeEnemy();
	

}; // end of Enemy class


#endif
