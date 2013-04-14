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
	ISceneManager *smgr,
	IVideoDriver *driver,
	IrrlichtDevice *device,
	IMetaTriangleSelector *metaTriSelector)
	: ObjectList(smgr, driver, device, metaTriSelector) // call super GameObject constructor first
{}

void Enemy::makeEnemy(){
	//testing with hardcoded position
	float xPos = 10200;
	float yPos = 70;
	float zPos = 10200;
	Soldier *newSoldier
		= new Soldier(
			this->smgr, this->driver, this->device,
			xPos, yPos, zPos
		);
	
	newSoldier->applyCollision(this->metaTriSelector);
}


