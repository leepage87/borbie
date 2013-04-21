/*
 */
#ifndef ENEMY_H
#define ENEMY_H


#include <irrlicht.h>
#include "objectList.h"
#include "soldier.h"



// define GameInstance to use pointer
class GameInstance;


// Enemy class: abstract, extends GameObject
class Enemy : public ObjectList {
	
	public:
	Enemy (irr::scene::IMetaTriangleSelector *metaTriSelector,
			GameInstance *gameInstance);

	//virtual void doDamage(int damage);
	void makeEnemy();
	void updateEnemy();

}; // end of Enemy class


#endif
