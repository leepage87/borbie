/*
 */
#ifndef ENEMY_H
#define ENEMY_H


#include <irrlicht.h>
#include "objectList.h"
#include "soldier.h"
#include "bigAssSoldier.h"
#include "updatable.h"



// define GameInstance to use pointer
class GameInstance;


// Enemy class: abstract, extends GameObject
class Enemies : public ObjectList, public Updatable {
  private:
    // creates a new enemy at position x, y, z
	void makeEnemy(float x, float y, float z);
	
  public:
	Enemies (irr::scene::IMetaTriangleSelector *metaTriSelector,
			GameInstance *gameInstance);

	//virtual void doDamage(int damage);
	virtual void generateObjects();
	virtual void update();

}; // end of Enemy class


#endif
