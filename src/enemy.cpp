/*	File: enemy.cpp
 *	Authors: idk your names
 *
 *	Description: ENEMIES!
 */

#include "enemy.h"
#include <iostream> // TODO: debug (remove)
using namespace std;

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;


Enemy::Enemy(
	IMetaTriangleSelector *metaTriSelector,
	GameInstance *gameInstance)
	// call super ObjectList constructor first:
	: ObjectList(metaTriSelector, gameInstance)
{}

void Enemy::makeEnemy(){
	//testing with hardcoded position
	float xPos = 10200;
	float yPos = 70;
	float zPos = 10200;
	Soldier *newSoldier
		= new Soldier(
			this->gameInstance,
			xPos, yPos, zPos
		);
	
	newSoldier->applyCollision(this->metaTriSelector);
	this->addObject(newSoldier);
}

void Enemy::updateEnemy(){
	int numObjs = objList.size();
        for(int j=0; j<numObjs; ++j){
			if(objList[j]){
				if(objList[j]->getNode()->isVisible())
            	((Soldier*)objList[j])->fire();
			}	
		}

}


