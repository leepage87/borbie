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


// GameObject class (abstract):
class GameObject {

  protected:
	// pointers to Irrlicht scene objects as needed
	irr::scene::ISceneManager *smgr;
	
	// internal Irrlicht scene node
	irr::scene::IMeshSceneNode *sceneNode;
	
	// object variables
	int health;


  public:
	// constructor: initializes standard object values, and saves the
	//	necessary Irrlicht object pointers to keep track of.
	GameObject(irr::scene::ISceneManager *smgr);
	// destructor: automatically removes the node from the scene.
	~GameObject();
	
	// standard getters
	virtual int getHealth() const;
	
	// pure virtual functions (override mandatory)
	virtual void doDamage(int damage) = 0;
	virtual void applyCollision(int metaOfNotIntType) = 0;
	
	
}; // end of GameObject class


#endif
