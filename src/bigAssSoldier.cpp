/*********************************************************************
 * File:     soldier.cpp
 * Authors:  Richard Teammco, Lee Page, Jonathan Miodownik
 * Function: This class creates big ass soldiers so you
 *           can throw cars at them and shit. Also allows them to aim
 *           their weapon and fire.
 *********************************************************************/
#include "bigAssSoldier.h"
#include "gameInstance.h"

using namespace std;

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

/*********************************************************************
 * Constructor for the big ass soldier
 * Param: gameInstance the game instance containing all necessary
 *        pointers
 * Param: posX the X coordinate at which the soldier will be spawned
 * Param: posY the Y coordinate at which the soldier will be spawned
 * Param: posZ the Z coordinate at which the soldier will be spawned
 *********************************************************************/
BigAssSoldier::BigAssSoldier(
	GameInstance *gameInstance,
	float posX, float posY, float posZ)
	// call super GameObject constructor first:
	: Soldier(gameInstance, posX, posY, posZ)
{
    this->BULLET_DAMAGE = 15;
    this->objectType = TYPE_ENEMY;
    this->sceneNode = smgr->addMeshSceneNode(
        smgr->getMesh("assets/models/enemies/soldier/armydude.obj"));
	this->sceneNode->setPosition(vector3df(posX, posY, posZ));
	this->sceneNode->setScale(vector3df(50,50,50));
	this->sceneNode->setVisible(true);
	this->sceneNode->setMaterialFlag(EMF_LIGHTING, true);
	this->sceneNode->setID(IDFlag_IsPickable);
	this->setHealth(1000);
    this->fireDelay = getRandomFireDelay();
}

int BigAssSoldier::lookAtPlayer(){
	//turn the soldier to look at you
	vector3df start = sceneNode->getPosition();
	start.Y += 500;
	vector3df end = gameInstance->getCamera()->getPosition();
	vector3df vect = end-start;
    vect = vect.getHorizontalAngle();
    vect.Y+=15;
	sceneNode->setRotation(vect);
	return (f32)start.getDistanceFrom(end);
}

/*********************************************************************
 * Overrides the Soldier class fire() method
 * Animates a muzzle flash billboard with firing sound and does
 * damage to borbie.  This method is only called when the soldier
 * is within range and has direct line of sight.  He has an 80%
 * chance of hitting his target.
 ********************************************************************/
void BigAssSoldier::fire(int distance){
	lastFireTime = gameInstance->getDevice()->getTimer()->getTime();
	IBillboardSceneNode * bill;
	bill = smgr->addBillboardSceneNode();
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
    bill->setMaterialTexture(0, driver->getTexture("assets/textures/muzFlash.png"));
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialFlag(video::EMF_ZBUFFER, false);
	float randomNum = Random::randomFloat(-101.0, 150.0);
	bill->setSize(core::dimension2d<f32>(300.0+randomNum, 300.0+randomNum));
	bill->setID(0);//not pickable by ray caster
		
	//get enemy position, adjust muzzle flash height to barrel
	vector3df start = sceneNode->getPosition();
	start.Y+=325;
	bill->setPosition(start);

    this->audioSystem->playSound3d(gameInstance->gunShot2, this);
	
	const int MUZZLE_FLASH_TIME = 50;
	
	ISceneNodeAnimator* anim =
	    gameInstance->getSceneManager()->createDeleteAnimator(MUZZLE_FLASH_TIME);
	bill->addAnimator(anim);
	anim->drop();
    if (!miss(distance))
	    gameInstance->player->applyBulletDamage(BULLET_DAMAGE);
    else
        gameInstance->player->ricochet();		
}


