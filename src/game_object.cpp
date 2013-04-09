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
	
	// ensure that internal node pointer is null
	this->sceneNode = 0;
	
	// set up default object values
	this->health = GAME_OBJ_MAXHEALTH;
	this->explosionRadius = GAME_OBJ_STDRADIUS;
}


/* DESTRUCTOR:
 *	Removes the Irrlicht IMeshSceneNode associated with this object from
 *	the game (if it exists).
 * NOTE: With inheritence, c++ automatically calls super destructors after
 *	child destructors are called. An overriding destructor needs not to
 *	delete the interal IMeshSceneNode. (I think)
 */
GameObject::~GameObject(){
	if(this->sceneNode)
		sceneNode->remove();
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


// updates animation timer. If finished, returns true. Otherwise, returns false.
bool GameObject::updateTimer(){
    if( this->explosionParticleSystem &&
        this->device->getTimer()->getTime() >= this->explosionStopTime)
    {
        this->explosionParticleSystem->setEmitter(0);
				this->explosionParticleSystemLarge->setEmitter(0);
        return true;
    }
    return false;
}

// Causes this object to explode, making it vanish, and return a particle
//	effect node animating the explosion effect in its current position.
void GameObject::explode(){
    // if an explosion already happened, remove it first
	if(this->explosionParticleSystem){
	    this->explosionParticleSystem->remove();
			this->explosionParticleSystemLarge->remove();
	}
	
	// add a new explosion particle system
    this->explosionParticleSystem =
		this->smgr->addParticleSystemSceneNode(false);

		this->explosionParticleSystemLarge =
		this->smgr->addParticleSystemSceneNode(false);
	
	// add the explosion emitter to the explosion particle system (pink sparkles)
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
	//explosionEmitter->drop();
	
	// add fade-out affector to the fire particle system
	IParticleAffector* explosionFadeOutAffector =
	    explosionParticleSystem->createFadeOutParticleAffector();
	this->explosionParticleSystem->addAffector(explosionFadeOutAffector);
	//explosionFadeOutAffector->drop();
	
	// customize the fire particle system positioning, etc.
	this->explosionParticleSystem->setPosition(this->sceneNode->getPosition());
	this->explosionParticleSystem->setScale(vector3df(45, 45, 45));
	this->explosionParticleSystem->setMaterialFlag(EMF_LIGHTING, false);
	this->explosionParticleSystem->setMaterialFlag(EMF_ZWRITE_ENABLE, false);
	this->explosionParticleSystem->setMaterialTexture(0,
	this->driver->getTexture("assets/textures/pinkfire.bmp")); // fire colored
	this->explosionParticleSystem->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);

//configure the large fireballs
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
	explosionEmitter->drop();
	
	// add fade-out affector to the fire particle system
	/*explosionFadeOutAffector =
	    explosionParticleSystemLarge->createFadeOutParticleAffector();*/
	this->explosionParticleSystemLarge->addAffector(explosionFadeOutAffector);
	explosionFadeOutAffector->drop();
	
	// customize the fire particle system positioning, etc.
	this->explosionParticleSystemLarge->setPosition(this->sceneNode->getPosition());
	this->explosionParticleSystemLarge->setScale(vector3df(45, 45, 45));
	this->explosionParticleSystemLarge->setMaterialFlag(EMF_LIGHTING, false);
	this->explosionParticleSystemLarge->setMaterialFlag(EMF_ZWRITE_ENABLE, false);
	this->explosionParticleSystemLarge->setMaterialTexture(0,
	this->driver->getTexture("assets/textures/fire.bmp")); // fire colored
	this->explosionParticleSystemLarge->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	
	// run this explosion for the predefined number of miliseconds.
	this->explosionStopTime = this->device->getTimer()->getTime() + 75;
	
	//this->sceneNode->remove();
}
