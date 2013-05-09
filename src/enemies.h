/*********************************************************************
 * File:     enemies.h
 * Authors:  Richard Teammco, Lee Page, Jonathan Miodownik
 * Function: This is the header file for enemies.cpp
 *********************************************************************/
#ifndef ENEMY_H
#define ENEMY_H


#include <irrlicht.h>
#include "objectList.h"
#include "soldier.h"
#include "bigAssSoldier.h"
#include "updatable.h"



// define GameInstance to use pointer
class GameInstance;


// Types of enemies
enum EnemyType {
    ENEMY_TYPE_SOLDIER,
    ENEMY_TYPE_BIG_ASS_SOLDIER
};


// Enemy class: extends GameObject, extends Updatable
class Enemies : public ObjectList, public Updatable {
  private:
    // creates a new enemy at position x, y, z
	void makeEnemy(float x, float y, float z, EnemyType type);
	
	// randomly creates an enemy near a randomly selected spawn point (exact
	//  position is also randomized by an offset). The enemy created is also
	//  random by a weighed percentage.
	void createRandomEnemy();
	
	// number of enemies
	unsigned int maxNumberEnemies;
	
	// next enemy spawn time
	unsigned int nextSpawnTime;
	
  public:
	Enemies (irr::scene::IMetaTriangleSelector *metaTriSelector,
			GameInstance *gameInstance);

    virtual void addMaxEnemies(unsigned int amount);
	virtual void generateObjects();
	virtual void update();

}; // end of Enemy class


#endif
