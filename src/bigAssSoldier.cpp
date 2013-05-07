/*	File: BigAssSoldier.cpp
 *	Authors: TYKS
 *	This class creates soldiers so you can throw cars at them and shit
 */

#include "bigAssSoldier.h"
#include "gameInstance.h"

using namespace std;

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

/*************************************************************
 * Constructor for the big ass soldier
 * Param: gameInstance the game instance containing all necessary pointers
 * Param: posX the X coordinate at which the soldier will be spawned
 * Param: posY the Y coordinate at which the soldier will be spawned
 * Param: posZ the Z coordinate at which the soldier will be spawned
 *************************************************************/
BigAssSoldier::BigAssSoldier(
	GameInstance *gameInstance,
	float posX, float posY, float posZ)
	// call super GameObject constructor first:
	: Soldier(gameInstance, posX, posY, posZ)
{
    this->BULLET_DAMAGE = 20;
    this->objectType = TYPE_ENEMY;
    this->sceneNode =
    	smgr->addMeshSceneNode(smgr->getMesh("assets/models/enemies/soldier/armydude.obj"));
	this->sceneNode->setPosition(vector3df(posX, posY, posZ));
	this->sceneNode->setScale(vector3df(50,50,50));
	this->sceneNode->setVisible(true);
	this->sceneNode->setMaterialFlag(EMF_LIGHTING, true);
	this->sceneNode->setID(IDFlag_IsPickable);
	this->setHealth(2000);

    this->fireDelay = getRandomFireDelay();


}


