/*	File: game_object.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class definition for the abstract
 *	class GameObject. GameObject is responsible for keeping track of most
 *	non-specific (abstract) information about Borbie scene objects that
 *	appear in the world, such as buildings, vehicles or NPCs.
 */

#include "game_object.h"
#include <iostream> // TODO - remove (debug)

/* CONSTRUCTOR:
 *	Copies the pointer to the Irrlicht engine scene manager, and initializes
 *	all variables to their default level.
 * To override this constructor, it is recommended to super-construct with
 *	this constructor first. You can do this by:
 *  ExtendedChild(int foo, int bar) : AbstractBase(foo) { ... }
 */
GameObject::GameObject(
	irr::scene::ISceneManager *smgr,
	irr::video::IVideoDriver *driver)
{
	// link reference to scene manager
	this->smgr = smgr;
	this->driver = driver;
	
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


// Causes this object to explode, making it vanish, and return a particle
//	effect node animating the explosion effect in its current position.
void GameObject::explode(){
	
	irr::scene::IParticleSystemSceneNode* ps =
		this->smgr->addParticleSystemSceneNode(false);
	
	irr::scene::IParticleEmitter* em = ps->createBoxEmitter(
		irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7), // emitter size
		irr::core::vector3df(0.0f,0.3f,0.0f),   // direction + speed
		4000,10000,                             // min,max particles per second
		irr::video::SColor(0,255,255,255),       // darkest color
		irr::video::SColor(0,255,255,255),      // brightest color
		250,1500,                        		// min,max lifetime
		0, 										// max angle degrees
		irr::core::dimension2df(10.f,10.f),      // min start size
		irr::core::dimension2df(20.f,20.f));     // max start size
	
	ps->setEmitter(em); // this grabs the emitter
	em->drop(); // so we can drop it here without deleting it
	
	irr::scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();
	
	ps->addAffector(paf); // same goes for the affector
	paf->drop();
	
	ps->setPosition(this->sceneNode->getPosition());
	ps->setScale(irr::core::vector3df(35,35,35));
	ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0, this->driver->getTexture("assets/textures/fire.bmp"));
	ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	
	
	//this->sceneNode->remove();
}






































