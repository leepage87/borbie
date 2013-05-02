/*	File: soldier.cpp
 *	Authors: idk your names
 *	
 *	This class creates soldiers so you can throw cars at them and shit
 */

#include "soldier.h"
#include "gameInstance.h"
#include "random.h"
#include <iostream> // TODO: debug (remove)
using namespace std;

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;


Soldier::Soldier(
	GameInstance *gameInstance,
	float posX, float posY, float posZ)
	// call super GameObject constructor first:
	: GameObject(gameInstance)
{
    this->objectType = TYPE_ENEMY;
    sceneNode =
    	smgr->addMeshSceneNode(smgr->getMesh("assets/models/enemies/soldier/armydude.obj"));
	sceneNode->setPosition(vector3df(posX, posY, posZ));
	sceneNode->setScale(vector3df(10,10,10));
	sceneNode->setVisible(true);
	sceneNode->setMaterialFlag(EMF_LIGHTING, true);
	sceneNode->setID(IDFlag_IsPickable);
	setHealth(350);
	lastFireTime = 0;
	moving = false;
    fireDelay = getRandomFireDelay() * 1000;
    std::cout<<"firedelay is:" << fireDelay<<std::endl;
	
}

void Soldier::applyCollision(
	irr::scene::IMetaTriangleSelector *metaTriSelector){
	// add its triangles to the global collision meta selector
	ITriangleSelector *selector =
		smgr->createTriangleSelectorFromBoundingBox(sceneNode);
	sceneNode->setTriangleSelector(selector);
	selector->drop();
	metaTriSelector->addTriangleSelector(sceneNode->getTriangleSelector());
}

int Soldier::getRandomFireDelay(){
    return Random::randomInt(1, 4);
}

void Soldier::updatePosition(){
    aim();
    isMoving();
}

void Soldier::isMoving(){
    if (sceneNode->getPosition() == destination)
        moving = false;
}

void Soldier::aim(){
	//turn the soldier to look at you
	vector3df start = sceneNode->getPosition();
	start.Y += 75;
	vector3df end = gameInstance->getCamera()->getPosition();
	end.Y -= 125;
	vector3df vect = end-start;
	sceneNode->setRotation(vect.getHorizontalAngle());
	length = (f32)start.getDistanceFrom(end);
    
	//Tactically operate oneself towards the enemy (Borbie)
    //in a high speed, low drag type of way
    //if enemy distance is between 5k-2k units
    if (!moving && length < 5000 && length > 2000)
        move();
    //Tactically attempt to bust a cap if Borbie is
    //within 4000 units
	if (length < 4000)
		targetRay();	
}

void Soldier::targetRay(){
	if(canShoot()){
		ray.end = sceneNode->getPosition();
		ray.start = gameInstance->getCamera()->getPosition();
	
		ISceneCollisionManager* collMan = gameInstance->getSceneManager()->getSceneCollisionManager();
		vector3df intersection;
		triangle3df hitTriangle;
	
		ISceneNode * selected =
			collMan->getSceneNodeAndCollisionPointFromRay(
			ray, intersection, hitTriangle, IDFlag_IsPickable, 0);
		if (selected == sceneNode)
            //bust a cap
			fire();	
	}
}

void Soldier::move(){
    moving = true;
    vector3df start = sceneNode->getPosition();
    destination = gameInstance->getCamera()->getPosition();
    destination.X = start.X + 0.2*(destination.X-start.X);
    destination.Z = start.Z + 0.2*(destination.Z-start.Z);
    destination.Y = 70;//ground height
    length = (f32)ray.start.getDistanceFrom(destination);
    const int SOLDIER_MOVE_SPEED = 1.75;
    f32 time = length * SOLDIER_MOVE_SPEED;
    ISceneNodeAnimator* anim =
            gameInstance->getSceneManager()->createFlyStraightAnimator(start,
            destination, time, false);
    sceneNode->addAnimator(anim);
    anim->drop();
}

bool Soldier::canShoot(){
	unsigned int currentTime = gameInstance->getDevice()->getTimer()->getTime();
	if (currentTime - lastFireTime  > fireDelay){
		return true;
    }
	return false;
}

void Soldier::fire(){
	lastFireTime = gameInstance->getDevice()->getTimer()->getTime();
	IBillboardSceneNode * bill;
	bill = smgr->addBillboardSceneNode();
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
    bill->setMaterialTexture(0, driver->getTexture("assets/textures/muzFlash.png"));
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialFlag(video::EMF_ZBUFFER, false);
	float randomNum = Random::randomFloat(-10.0, 15.0);
	bill->setSize(core::dimension2d<f32>(30.0+randomNum, 30.0+randomNum));
	bill->setID(0);//not pickable by ray caster
		
	//get enemy position, adjust muzzle flash height to barrel
	vector3df start = sceneNode->getPosition();
	start.Y+=60;
	bill->setPosition(start);
	
	const int MUZZLE_FLASH_TIME = 50;
	
	ISceneNodeAnimator* anim = gameInstance->getSceneManager()->createDeleteAnimator(MUZZLE_FLASH_TIME);
	bill->addAnimator(anim);
	anim->drop();
    if (!miss())
	    gameInstance->player->applyDamage(3);		
}

bool Soldier::miss(){
    if (Random::randomInt(1,6) <= 4){//20% chance
        return false;
    }
    return true;
}

// Causes this object to explode, making it vanish, and return a particle
//	effect node animating the explosion effect in its current position.
void Soldier::createExplosionEffect(){
	// add a new explosion particle systems (for the two intermixed explosions)
    this->explosionParticleSystem =
		this->smgr->addParticleSystemSceneNode(false);
    this->explosionParticleSystemLarge =
        this->smgr->addParticleSystemSceneNode(false);
    
	// add an emitter for BLOODSPLOSION!!!!!!!!!!!!!!!
	IParticleEmitter *explosionEmitter =
	    this->explosionParticleSystem->createBoxEmitter(
		    aabbox3d<f32>(-5, 0, -5, 5, 1, 5),  // emitter size
		    vector3df(0.0f,0.0f,0.1f),          // direction + speed
		    12000, 140000,                       // min,max particles per second
		    SColor(0,255,255,255),              // darkest color
		    SColor(0,255,255,255),              // brightest color
		    200, 800,                          // min, max particle lifetime
		    360,                                // max angle degrees
		    dimension2df(20.0f, 20.0f),         // min start size
		    dimension2df(40.0f, 40.0f));        // max start size
	this->explosionParticleSystem->setEmitter(explosionEmitter);
	explosionEmitter->drop(); // drop (re-created later)
	
	//add gravity affector to pink sparkles
	IParticleGravityAffector* pgaf = explosionParticleSystem->createGravityAffector
											(vector3df(0.F,-0.2F,0.0F), 200U);
	explosionParticleSystem->addAffector(pgaf);
    pgaf->drop();

	// add fade-out affector to the fire particle system
	IParticleAffector* explosionFadeOutAffector =
	    explosionParticleSystem->createFadeOutParticleAffector();
	this->explosionParticleSystem->addAffector(explosionFadeOutAffector);
	explosionFadeOutAffector->drop();
	
	// customize the first fire particle system positioning, etc.
	vector3df explosionPos = this->sceneNode->getPosition();
	if(explosionPos.Y < 0) // adjust position: no explosions underground!
	    explosionPos.Y = 0;

	// adjust the blood
	this->explosionParticleSystem->setPosition(explosionPos);
	this->explosionParticleSystem->setScale(vector3df(45, 45, 45));
	this->explosionParticleSystem->setMaterialFlag(EMF_LIGHTING, false);
	this->explosionParticleSystem->setMaterialFlag(EMF_ZWRITE_ENABLE, false);
	this->explosionParticleSystem->setMaterialTexture(0,
	this->driver->getTexture("assets/textures/blood.bmp"));
	this->explosionParticleSystem->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	
	std::cout << "Soldier gone boom " << std::endl;
}
