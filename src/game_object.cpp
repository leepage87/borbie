/*	File: game_object.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class definition for the abstract
 *	class GameObject. GameObject is responsible for keeping track of most
 *	non-specific (abstract) information about Borbie scene objects that
 *	appear in the world, such as buildings, vehicles or NPCs.
 */

#include "game_object.h"
#include "game.h"

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
GameObject::GameObject(
	irr::scene::ISceneManager *smgr,
	irr::video::IVideoDriver *driver,
	IrrlichtDevice *device)
{
	// link reference to scene manager
	this->smgr = smgr;
	this->driver = driver;
	this->device = device;
	
	this->explosionParticleSystem = 0;
	this->explosionParticleSystemLarge = 0;
	this->hasBeenExploded = false;
	this->timeToDelete = 0;
	
	this->updateMode = GAME_OBJ_MODE_IDLE;
	
	// ensure that internal node pointer is null
	this->sceneNode = 0;
	
	// set up default object values
	this->health = GAME_OBJ_MAXHEALTH;
	this->explosionRadius = GAME_OBJ_STDRADIUS;
}


/* DESTRUCTOR:
 *	Removes the Irrlicht IMeshSceneNode associated with this object from
 *	the game (if it exists), as well as all of its associated particle systems.
 * NOTE: With inheritence, c++ automatically calls super destructors after
 *	child destructors are called. An overriding destructor needs not to
 *	delete the interal IMeshSceneNode.
 */
GameObject::~GameObject(){
	if(this->sceneNode)
		sceneNode->remove();
    if(this->explosionParticleSystem)
        explosionParticleSystem->remove();
    if(this->explosionParticleSystemLarge)
        explosionParticleSystemLarge->remove();
}


/* GET: health
 *	returns the object's current health (in int form)
 */
int GameObject::getHealth() const {
	return this->health;
}

/* GET: explosion radius
 *	returns the object's current explosion radius (in int form).
 */
int GameObject::getExplosionRadius() const {
	return this->explosionRadius;
}


/* SET: health
 *	set the objects current health
 */
void GameObject::setHealth(int newHealth){
	this->health = newHealth;
}

/* SET: explosion radius
 *	set the objects current explosion radius
 */
void GameObject::setExplosionRadius(int newRadius){
	this->health = newRadius;
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
            this->timeToDelete = curTime + 5000; // delete after 5 seconds
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
		    vector3df(0.0f,2.0f,0.0f),          // direction + speed
		    12000, 14000,                       // min,max particles per second
		    SColor(0,255,255,255),              // darkest color
		    SColor(0,255,255,255),              // brightest color
		    200, 2500,                          // min, max particle lifetime
		    360,                                // max angle degrees
		    dimension2df(30.0f, 30.0f),         // min start size
		    dimension2df(50.0f, 50.0f));        // max start size
	this->explosionParticleSystem->setEmitter(explosionEmitter);
	explosionEmitter->drop(); // drop (re-created later)
	
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
	
	this->sceneNode->setVisible(false);
}
