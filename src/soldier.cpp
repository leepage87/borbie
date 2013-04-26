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
    sceneNode =
    	smgr->addAnimatedMeshSceneNode(smgr->getMesh("assets/models/enemies/green_army_man.3DS"));
	sceneNode->setPosition(vector3df(posX, posY, posZ));
	sceneNode->setScale(vector3df(0.7,0.7,0.7));
	sceneNode->setVisible(true);
	sceneNode->setMaterialFlag(EMF_LIGHTING, false);
	setHealth(350);
}

void Soldier::applyCollision(
	irr::scene::IMetaTriangleSelector *metaTriSelector)
{
	// add its triangles to the global collision meta selector
	ITriangleSelector *selector =
		smgr->createTriangleSelectorFromBoundingBox(sceneNode);
	sceneNode->setTriangleSelector(selector);
	selector->drop();
	metaTriSelector->addTriangleSelector(sceneNode->getTriangleSelector());
}

void Soldier::fire(){
	//create the billboard for the "bullet"
	IBillboardSceneNode * bill;
	bill = smgr->addBillboardSceneNode();
    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
    bill->setMaterialTexture(0, driver->getTexture("assets/textures/particle.bmp"));
    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialFlag(video::EMF_ZBUFFER, false);
    bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));
    bill->setID(0);//not pickable by ray caster



	//hard coded target for testing
	float posAdjust[3];
	vector3df end = (gameInstance->getCamera()->getPosition());
	end.Y-=30;

	//get enemy position, adjust bullet height to barrel
	vector3df start = sceneNode->getPosition();
	start.Y+=45;

	//get the length of the distance we're shooting
	f32 length = (f32)start.getDistanceFrom(end);
	
	const float maxDistance = 10000;
	
	//vector3df bulletEnd = end;
	if (length < 4000){
		int offsetX = Random::randomInt(-40,40);
		int offsetY = Random::randomInt(-40,40);
		int offsetZ = Random::randomInt(-40,40);
		float scale = maxDistance/length;
		float diffX = end.X - start.X;
		float diffY = end.Y - start.Y;
		float diffZ = end.Z - start.Z;
		end.X = start.X + diffX * scale + offsetX*scale;
		end.Y = start.Y + diffY * scale + offsetY*scale;
		end.Z = start.Z + diffZ * scale + offsetZ*scale;
		const f32 SPEED = 14.0f;
		//Borbie's Shit Adventure: Let's Fuck the Town!
		//figure out how long it should take to get there, so the animator SPEED is constant
		f32 length2 = (f32) start.getDistanceFrom(end);
		u32 time = (u32)(length2 / SPEED);

		ISceneNodeAnimator* anim = gameInstance->getSceneManager()->createFlyStraightAnimator(start, end, time);
		bill->addAnimator(anim);
		anim->drop();
		anim = gameInstance->getSceneManager()->createDeleteAnimator(time);
		bill->addAnimator(anim);
		anim->drop();
	}

	//turn the soldier to look at you
	end.Y -= 125;
	vector3df vect = start-end;
	sceneNode->setRotation(vect.getHorizontalAngle());
	
}

// Causes this object to explode, making it vanish, and return a particle
//	effect node animating the explosion effect in its current position.
void Soldier::explode(){
    // TODO - make explosion size scale with this->explosionRadius

    // if already exploded, don't do it again
    if(this->hasBeenExploded)
        return;
    
	// add a new explosion particle systems (for the two intermixed explosions)
    this->explosionParticleSystem =
		this->smgr->addParticleSystemSceneNode(false);
    this->explosionParticleSystemLarge =
        this->smgr->addParticleSystemSceneNode(false);

	// add an emitter to the first explosion particle system (pink sparkles)
	IParticleEmitter *explosionEmitter =
	    this->explosionParticleSystem->createBoxEmitter(
		    aabbox3d<f32>(-5, 0, -5, 5, 1, 5),  // emitter size
		    vector3df(0.0f,0.0f,0.1f),          // direction + speed
		    12000, 14000,                       // min,max particles per second
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
	// DO NOT DROP! - recycling it for the second particle system
	
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
/*
    // configure the large fireballs for the second (larger) particle system
    explosionEmitter =
        this->explosionParticleSystemLarge->createBoxEmitter(
		    aabbox3d<f32>(-5, 0, -5, 5, 1, 5),  // emitter size
		    vector3df(0.0f,0.5f,0.0f),          // direction + speed
		    300, 700,                       // min,max particles per second
		    SColor(0,255,255,255),              // darkest color
		    SColor(0,255,255,255),              // brightest color
		    200, 1000,                          // min, max particle lifetime
		    360,                                // max angle degrees
		    dimension2df(400.0f, 400.0f),         // min start size
		    dimension2df(700.0f, 700.0f));        // max start size
	this->explosionParticleSystemLarge->setEmitter(explosionEmitter);
	explosionEmitter->drop(); // clean up emitter
	
	// add the same fade-out affector to the second fire particle system
	this->explosionParticleSystemLarge->addAffector(explosionFadeOutAffector);
	explosionFadeOutAffector->drop(); // drop - done with it now
	
	// customize the second fire particle system positioning, etc.
	this->explosionParticleSystemLarge->setPosition(explosionPos);
	this->explosionParticleSystemLarge->setScale(vector3df(45, 45, 45));
	this->explosionParticleSystemLarge->setMaterialFlag(EMF_LIGHTING, false);
	this->explosionParticleSystemLarge->setMaterialFlag(EMF_ZWRITE_ENABLE, false);
	this->explosionParticleSystemLarge->setMaterialTexture(0,
	this->driver->getTexture("assets/textures/fire.bmp")); // fire colored
	this->explosionParticleSystemLarge->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	*/
	// run this explosion for the predefined number of miliseconds.
	this->explosionStopTime = this->device->getTimer()->getTime()
	    + GAME_OBJ_EXPLOSION_TIME_MS;
	this->updateMode = GAME_OBJ_MODE_EXPLODED;
	
	// set the node visible, and remove it from the global collision meta
	this->sceneNode->setVisible(false);
	this->gameInstance->removeCollision(this->sceneNode->getTriangleSelector());
	
	// add this object to the GameInstance's updator to keep the timers going
	this->gameInstance->addUpdateObject(this);
	//attempt at splash damage on exploding buildings and shit
	//this->gameInstance->applyExplosionDamage(this);
}
