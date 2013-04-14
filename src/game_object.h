/*	File: game_object.h
 *	Authors: teamKillYourself
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

// declare ObjectList - (ObjectList in objectList.h): GameObject is included
//  in that header.
class ObjectList;


// GameObject standard values
//	TODO: modify as needed
#define GAME_OBJ_MAXHEALTH 1000
#define GAME_OBJ_EXPLOSION_RADIUS 1000
#define GAME_OBJ_EXPLOSION_DAMAGE 1000

// timer value constants
#define GAME_OBJ_EXPLOSION_TIME_MS 75
#define GAME_OBJ_DELETE_TIME_MS 5000


// define update return values: what to do after update is called
#define GAME_OBJ_DO_NOTHING 0 // do nothing (keep the object in the update list)
#define GAME_OBJ_REMOVE_FROM_UPDATE_LIST 1 // remove it from the update list
#define GAME_OBJ_DELETE 2 // call delete on the object (and remove from list)

// define update modes:
#define GAME_OBJ_MODE_IDLE 0
#define GAME_OBJ_MODE_EXPLODED 1
#define GAME_OBJ_MODE_PENDING_DELETE 2


// GameObject class (abstract):
class GameObject {

  protected:
	// pointers to Irrlicht scene objects as needed
	irr::scene::ISceneManager *smgr;
	irr::video::IVideoDriver *driver;
	irr::IrrlichtDevice *device;
	
	// internal Irrlicht scene node
	irr::scene::IMeshSceneNode *sceneNode;
	
	// object variables
	int health;
	int explosionRadius;
	int explosionDamage;
	
	// explosion variables
	irr::scene::IParticleSystemSceneNode *explosionParticleSystem;
	irr::scene::IParticleSystemSceneNode *explosionParticleSystemLarge;
	irr::u32 explosionStopTime;
	bool hasBeenExploded;
	
	// returns an invisible Irrlicht node (sphere) that represents the collision
	//  of the object's explosion radius.
	virtual irr::scene::ISceneNode* getExplosionSphere();
	
	// memory management - because Irrlicht is too crap to provide this basic
	//  functionality that should be trivial in any system like this.
	// Used to update each frame to manage events and memory (you know,
	//  features Irrlicht should have provided out of the box).
	unsigned int updateMode;
	unsigned int timeToDelete;


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
	virtual void explode();
	virtual bool hasExploded(); // returns TRUE if this object has exploded
	
	virtual void applyExplosionDamage(int numLists, ...);
	
	// updates the object's animation/effects and other possible timers;
	// RETURNS: value (defined as constants above) of action that the
	//  caller of this update function should take on this object.
	virtual unsigned int update();
	
	
	// pure virtual functions (override mandatory)
	virtual void doDamage(int damage) = 0;
	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		) = 0;
	
}; // end of GameObject class


#endif
