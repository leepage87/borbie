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
// similarly, GameInstance is used
class GameInstance;


// GameObject standard values
//	TODO: modify as needed
#define GAME_OBJ_MAXHEALTH 1000
#define GAME_OBJ_EXPLOSION_RADIUS 1000
#define GAME_OBJ_EXPLOSION_DAMAGE 500

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


struct CollisionSphere {
    irr::scene::ISceneNode *sphere;
    irr::scene::ISceneNodeAnimator* collisionAnimator;
};


// GameObject class (abstract):
class GameObject {

    // declare friend to have access to all of GameObject's members
    friend class ObjectList;

  protected:
	// pointers to Irrlicht scene objects as needed
	irr::scene::ISceneManager *smgr;
	irr::video::IVideoDriver *driver;
	irr::IrrlichtDevice *device;
	
	// internal Irrlicht scene node and global meta triangle selector
	irr::scene::IMeshSceneNode *sceneNode;
	irr::scene::IMetaTriangleSelector *metaTriSelector;
	
	// pointer to gameInstance (to add itself to the updator)
	GameInstance *gameInstance;
	
	// allow a triangle selector to be set here
	void setMetaTriSelector(irr::scene::IMetaTriangleSelector *metaTriSelector);
	
	// object variables
	int health;
	int explosionRadius;
	int explosionDamage;
	
	// explosion variables
	irr::scene::IParticleSystemSceneNode *explosionParticleSystem;
	irr::scene::IParticleSystemSceneNode *explosionParticleSystemLarge;
	irr::u32 explosionStopTime;
	bool hasBeenExploded;
	
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
				irr::IrrlichtDevice *device,
				GameInstance *gameInstance);
	// destructor: automatically removes the node from the scene.
	virtual ~GameObject();
	
	// TODO - perhaps these can be private, and only friend-accessible
	// standard getters
	virtual int getHealth() const;
	virtual int getExplosionRadius() const;
	virtual int getExplosionDamage() const;
	virtual irr::scene::IMeshSceneNode* getNode() { return this->sceneNode; }
	
	// standard setters
	virtual void setHealth(int newHealth);
	virtual void setExplosionRadius(int newRadius);
	virtual void setExplosionDamage(int newDamage);
	
	// Apply damage to this node. To "heal", apply negative damage. Damage
	//  applied may automatically change the visible state of this object,
	//  based on its health. If damage causes this object's heatlth to dip
	//  to or below 0, this object also explodes.
	virtual void applyDamage(int amount);
	
	// Causes this object to explode, creating a particle effect around it.
	//  For the explosion to fade out, it is necessary to call update() each
	//  frame until update() returns true (implying explosion is finished).
	virtual void explode();
	virtual bool hasExploded(); // returns TRUE if this object has exploded
	
	// if this node exploded, apply explosion damage around its own explosion
	//  radius (scaled based on distance from explosion center), and apply
	//  the appropriate amount of explosion damage.
	virtual void applyExplosionDamage(int numLists, ...);
	
	// updates the object's animation/effects and other possible timers;
	// RETURNS: value (defined as constants above) of action that the
	//  caller of this update function should take on this object.
	virtual unsigned int update();
	
	
	// pure virtual functions (override mandatory)
	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		) = 0;
	
}; // end of GameObject class


#endif
