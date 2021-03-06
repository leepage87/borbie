/********************************************************************* 
 *	File: game_object.h
 *	Authors:  Richard Teammco, Lee Page, Jonathan Miodownik
 *
 *	Description: this file contains the class declaration for the abstract
 *	class GameObject. GameObject is responsible for keeping track of most
 *	non-specific (abstract) information about Borbie scene objects that
 *	appear in the world, such as buildings, vehicles or NPCs.
 *	This abstract class that provides an interface of functions and values
 *	for all interactive game objects.
 *********************************************************************/

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


// include irrlicht
#include <irrlicht.h>


// declare ObjectList - (ObjectList in objectList.h): GameObject is included
//  in that header.
class ObjectList;
// similarly, GameInstance and AudioSystem is used
class GameInstance;
class AudioSystem;


// GameObject standard (default) values
//	TODO: modify as needed
#define GAME_OBJ_MAXHEALTH 1000
#define GAME_OBJ_EXPLOSION_RADIUS 1500
#define GAME_OBJ_EXPLOSION_DAMAGE 400

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


// GameObject types: used to differentiate
enum GameObjectType {
    NO_TYPE, // default
    TYPE_BUILDING,
    TYPE_VEHICLE,
    TYPE_ENEMY,
    TYPE_BORBIE
};


// Declare ObjectList to save pointers to it
class ObjectList;


// GameObject class (abstract):
class GameObject {

  // declare friend to have access to all of GameObject's members
  friend class ObjectList;
	
  protected: // function calls for ObjectList to use
	void setMetaTriSelector(irr::scene::IMetaTriangleSelector *metaTriSelector);
	void setContainer(ObjectList *objList);

  protected:
	// pointers to Irrlicht scene objects as needed
	irr::scene::ISceneManager *smgr;
	irr::video::IVideoDriver *driver;
	irr::IrrlichtDevice *device;
	
	// internal Irrlicht scene node and global meta triangle selector
	irr::scene::ISceneNode *sceneNode;
	irr::scene::IMetaTriangleSelector *metaTriSelector;
	
	// pointer to object list containing this object
	ObjectList *containerList;
	
	// pointer to the audio system
	AudioSystem *audioSystem;
	
	// pointer to gameInstance (to add itself to the updator)
	GameInstance *gameInstance;
	
	// object variables
	int startingHealth;
	int health;
	int explosionRadius;
	int explosionDamage;
	
	// object type
	GameObjectType objectType;
	
	// explosion variables
	virtual void createExplosionEffect(); // create the particles
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
	GameObject(GameInstance *gameInstance);
	// destructor: automatically removes the node from the scene.
	virtual ~GameObject();
	
	// standard getters for object data
	virtual GameObjectType getObjectType() const;
	virtual int getHealth() const;
	virtual int getExplosionRadius() const;
	virtual int getExplosionDamage() const;
	virtual irr::scene::ISceneNode* getNode() { return this->sceneNode; }
	
	// standard setters
	virtual void setHealth(int newHealth);
	virtual void setMaxHealth(int newHealth);
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
	
	// updates the object's animation/effects and other possible timers;
	// RETURNS: value (defined as constants above) of action that the
	//  caller of this update function should take on this object.
	virtual unsigned int updateTimers();
	
	
	// pure virtual functions (override mandatory)
	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		) = 0;
	
}; // end of GameObject class


#endif
