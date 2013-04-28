/*	File: game_object.cpp
 *	Authors: teamKillYourself
 *
 *	Description: this file contains the class definition for the abstract
 *	class GameObject. GameObject is responsible for keeping track of most
 *	non-specific (abstract) information about Borbie scene objects that
 *	appear in the world, such as buildings, vehicles or NPCs.
 */

// application headers
#include "gameObject.h"
#include "objectList.h"
#include "game.h"
#include "gameInstance.h"

// used for c++ variable arguments
#include <cstdarg>

// TODO - remove
#include <iostream>

// Irrlicht namespaces
using namespace irr;
using namespace scene;
using namespace core;
using namespace video;


/* CONSTRUCTOR:
 *	Copies the pointer to the Irrlicht engine scene manager, and initializes
 *	all variables to their default level.
 * To override this constructor, it is recommended to super-construct with
 *	this constructor first. You can do this by:
 *  ExtendedChild(int foo, int bar) : AbstractBase(foo) { ... }
 */
GameObject::GameObject(GameInstance *gameInstance){
	// link pointers to Irrlicht objects
	this->smgr = gameInstance->getSceneManager();
	this->driver = gameInstance->getDriver();
	this->device = gameInstance->getDevice();
	
	// link pointer to game instance
	this->gameInstance = gameInstance;
	
	// default values
	this->health = GAME_OBJ_MAXHEALTH;
	this->explosionRadius = GAME_OBJ_EXPLOSION_RADIUS;
	this->explosionDamage = GAME_OBJ_EXPLOSION_DAMAGE;
	this->hasBeenExploded = false;
	this->timeToDelete = 0;
	
	// set all pointers to null initially
	this->sceneNode = 0;
	this->explosionParticleSystem = 0;
	this->explosionParticleSystemLarge = 0;
	
	// start mode on idle (not doing anything with updates)
	this->updateMode = GAME_OBJ_MODE_IDLE;
	
	
}


/* DESTRUCTOR:
 *	Removes the Irrlicht ISceneNode associated with this object from
 *	the game (if it exists), as well as all of its associated particle systems.
 * NOTE: With inheritence, c++ automatically calls super destructors after
 *	child destructors are called. An overriding destructor needs not to
 *	delete the interal ISceneNode.
 */
GameObject::~GameObject(){
	if(this->sceneNode){
		this->sceneNode->remove();
		this->sceneNode = 0;
	}
    if(this->explosionParticleSystem){
        explosionParticleSystem->remove();
        explosionParticleSystem = 0;
    }
    if(this->explosionParticleSystemLarge){
        explosionParticleSystemLarge->remove();
        explosionParticleSystemLarge = 0;
    }
}


// (private, friend-accessible by ObjectList's addObject function)
// Set the meta triangle selector to the given selector.
void GameObject::setMetaTriSelector(IMetaTriangleSelector *metaTriSelector){
    this->metaTriSelector = metaTriSelector;
}


// this is hackery!
void GameObject::applyExplosionDamage(int numLists, ...){
    // get list of function arguments
    va_list args;
    va_start(args, numLists);
    
    // get this node's position (optimizing!)
    vector3df explodePos = this->sceneNode->getPosition();
    
    // iterate through the list of arguments
    for(int i=0; i<numLists; ++i){
        ObjectList *objects = va_arg(args, ObjectList *);
        // iterate through each list and check if it's close enough to this obj
        int numObjs = objects->objList.size();
        for(int j=0; j<numObjs; ++j){
            ISceneNode *curNode = objects->objList[j]->getNode();
            // if this (thrown) object IS the current node, ignore it
            if(curNode == this->sceneNode)
                continue;
            // if this (thrown) node is NOT visible, ignore it
            else if(!curNode->isVisible())
                continue;
            // otherwise, check if the distance is close enough, and apply damage
            //  based on the distance to the explosion center
            float distance = curNode->getPosition().getDistanceFrom(explodePos);
            if(distance <= this->explosionRadius){
                int damage = this->explosionDamage; // max damage
                if(distance > 400){ // if more than 400 away, scale down damage
                    float scale = (distance-400) / (this->explosionRadius-400);
                    damage = int(this->explosionDamage * scale);
                }
                objects->objList[j]->applyDamage(damage);
                std::cout << "Damaged @distance=" << distance <<
                    " for @damage=" << damage << std::endl;
            }
        }
    }
    
    // done with arguments
    va_end(args);
}


// GET: health - returns the object's current health (in int form)
int GameObject::getHealth() const {
	return this->health;
}

// GET: explosion radius - returns the object's current explosion radius (int).
int GameObject::getExplosionRadius() const {
	return this->explosionRadius;
}

// GET: explosion radius - returns the object's current explosion radius (int).
int GameObject::getExplosionDamage() const {
	return this->explosionDamage;
}


// SET: health - set the objects current health
void GameObject::setHealth(int newHealth){
	this->health = newHealth;
}

// SET: explosion radius - set the objects current explosion radius
void GameObject::setExplosionRadius(int newRadius){
	this->explosionRadius = newRadius;
}

// SET: explosion damage - set the objects current explosion damage
void GameObject::setExplosionDamage(int newDamage){
	this->explosionDamage = newDamage;
}

void GameObject::applyDamage(int amount){
    this->health -= amount;
    if(this->health <= 0){
        this->health = 0;
        std::cout << "GameObject called explode" << std::endl;
        this->explode();
    }
}


// updates all timers. If a timer is finished, returns the correct action to
//  take upon this happening. If this update was called for no reason, then
//  GAME_OBJ_REMOVE_FROM_UPDATE_LIST will be returned, indicating that this
//  object should no longer be updated each frame.
unsigned int GameObject::update(){
    // if object was exploded, check if explosion timer is up. If so, keep it
    //  in the list but flag it for deleting.
    if(this->updateMode == GAME_OBJ_MODE_EXPLODED){
        unsigned int curTime = this->device->getTimer()->getTime();
        if(curTime >= this->explosionStopTime) { // if explosion is done
            // stop the explosion
            this->explosionParticleSystem->setEmitter(0);
            this->explosionParticleSystemLarge->setEmitter(0);
            this->hasBeenExploded = true;
            this->updateMode = GAME_OBJ_MODE_PENDING_DELETE;
            // delete after 5 seconds
            this->timeToDelete = curTime + GAME_OBJ_DELETE_TIME_MS;
        }
        return GAME_OBJ_DO_NOTHING; // do nothing to the object in this mode
    }
    
    // if object is waiting to be deleted, then check if time to delete timer
    //  is up. If so, return the correct value to be deleted from the game.
    else if(this->updateMode == GAME_OBJ_MODE_PENDING_DELETE){
        unsigned int curTime = this->device->getTimer()->getTime();
        if(curTime >= this->timeToDelete) {
            return GAME_OBJ_DELETE; // if deleted, say so
        }
        else
            return GAME_OBJ_DO_NOTHING; // otherwise, do nothing so far
    }
    
    // if object is idle, or otherwise not flagged, it shouldn't be updated
    else
        return GAME_OBJ_REMOVE_FROM_UPDATE_LIST;
}


// returns TRUE if this object was already exploded (if timer ticked out and
//  explosion occured) - false if not yet exploded or if explode was never
//  called.
bool GameObject::hasExploded(){
    return this->hasBeenExploded;
}


// Causes this object to explode, making it vanish, and return a particle
//	effect node animating the explosion effect in its current position.
void GameObject::explode(){
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
		    vector3df(0.0f,0.0f,0.2f),          // direction + speed
		    12000, 14000,                       // min,max particles per second
		    SColor(0,255,255,255),              // darkest color
		    SColor(0,255,255,255),              // brightest color
		    200, 1250,                          // min, max particle lifetime
		    360,                                // max angle degrees
		    dimension2df(30.0f, 30.0f),         // min start size
		    dimension2df(50.0f, 50.0f));        // max start size
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

	
	// adjust the pink sparkes explosion position and rendering values
	this->explosionParticleSystem->setPosition(explosionPos);
	this->explosionParticleSystem->setScale(vector3df(45, 45, 45));
	this->explosionParticleSystem->setMaterialFlag(EMF_LIGHTING, false);
	this->explosionParticleSystem->setMaterialFlag(EMF_ZWRITE_ENABLE, false);
	this->explosionParticleSystem->setMaterialTexture(0,
	this->driver->getTexture("assets/textures/pinkfire.bmp")); // fire colored
	this->explosionParticleSystem->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);

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
