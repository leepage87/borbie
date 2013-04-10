/*	File: game_object.h
 *	Authors: idk your names
 *
 *	Description: this file contains the class declaration for the abstract
 *	class GameObject. GameObject is responsible for keeping track of most
 *	non-specific (abstract) information about Borbie scene objects that
 *	appear in the world, such as buildings, vehicles or NPCs.
 *	This abstract class that provides an interface of functions and values
 *	for all interactive game objects.
 */

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


// include irrlicht
#include <irrlicht.h>

// GameObject definitions
//	TODO: modify as needed
#define GAME_OBJ_MAXHEALTH 1000
#define GAME_OBJ_STDRADIUS 1000

#define GAME_OBJ_EXPLOSION_TIME_MS 75


// GameObject class (abstract):
class GameObject {

  protected:
	// pointers to Irrlicht scene objects as needed
	irr::scene::ISceneManager *smgr;
	irr::video::IVideoDriver *driver;
	irr::IrrlichtDevice *device;
	
	// internal Irrlicht scene node
	irr::scene::IMeshSceneNode *sceneNode;
	
	// explosion variables
	irr::scene::IParticleSystemSceneNode *explosionParticleSystem;
	irr::scene::IParticleSystemSceneNode *explosionParticleSystemLarge;
	irr::u32 explosionStopTime;
	bool hasBeenExploded;
	
	// object variables
	int health;
	int explosionRadius;
	bool pickUp; // TODO - is this used?


  public:
	// constructor: initializes standard object values, and saves the
	//	necessary Irrlicht object pointers to keep track of.
	GameObject(	irr::scene::ISceneManager *smgr,
				irr::video::IVideoDriver *driver,
				irr::IrrlichtDevice *device);
	// destructor: automatically removes the node from the scene.
	~GameObject();
	
	// standard getters
	virtual int getHealth() const;
	virtual int getExplosionRadius() const;
	virtual irr::scene::IMeshSceneNode* getNode() { return this->sceneNode; }
	
	// standard setters
	virtual void setHealth(int newHealth);
	virtual void setExplosionRadius(int newRadius);
	
	// Causes this object to explode, creating a particle effect around it.
	//  For the explosion to fade out, it is necessary to call update() each
	//  frame until update() returns true (implying explosion is finished).
	// TODO: object should also disappear here (be set to invisible)
	virtual void explode();
	virtual bool hasExploded(); // returns TRUE if this object has exploded
	
	// updates the object's animation/effects timer
	// TODO: perhaps change name to just update() - maybe
	virtual bool updateTimer();
	
	
	// pure virtual functions (override mandatory)
	virtual void doDamage(int damage) = 0;
	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		) = 0;
	
}; // end of GameObject class


#endif
