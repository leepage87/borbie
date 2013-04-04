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


// GameObject class (abstract):
class GameObject {

  protected:
	// pointers to Irrlicht scene objects as needed
	irr::scene::ISceneManager *smgr;
	irr::video::IVideoDriver *driver;
	
	// internal Irrlicht scene node
	irr::scene::IMeshSceneNode *sceneNode;
	
	// object variables
	int health;
	int explosionRadius;


  public:
	// constructor: initializes standard object values, and saves the
	//	necessary Irrlicht object pointers to keep track of.
	GameObject(	irr::scene::ISceneManager *smgr,
				irr::video::IVideoDriver *driver = 0);
	// destructor: automatically removes the node from the scene.
	~GameObject();
	
	// standard getters
	virtual int getHealth() const;
	virtual int getExplosionRadius() const;
	virtual irr::scene::IMeshSceneNode* getNode() { return this->sceneNode; }
	
	// standard setters
	virtual void setHealth(int newHealth);
	virtual void setExplosionRadius(int newRadius);
	
	// Causes this object to explode, making it vanish, and return a particle
	//	effect node animating the explosion effect in its current position.
	virtual void explode();
	
	
	// pure virtual functions (override mandatory)
	virtual void doDamage(int damage) = 0;
	virtual void applyCollision(
			irr::scene::IMetaTriangleSelector *metaTriSelector
		) = 0;
	
	
}; // end of GameObject class


#endif
