/*	File: game_object.cpp
 *	Authors: idk your names
 *
 *	Description: this file contains the class definition for the abstract
 *	class GameObject. GameObject is responsible for keeping track of most
 *	non-specific (abstract) information about Borbie scene objects that
 *	appear in the world, such as buildings, vehicles or NPCs.
 */

#include "game_object.h"


/* CONSTRUCTOR:
 *	Copies the pointer to the Irrlicht engine scene manager, and initializes
 *	all variables to their default level.
 * To override this constructor, it is recommended to super-construct with
 *	this constructor first. You can do this by:
 *  ExtendedChild(int foo, int bar) : AbstractBase(foo) { ... }
 */
GameObject::GameObject(irr::scene::ISceneManager *smgr){
	// link reference to scene manager
	this->smgr = smgr;
	
	// ensure that internal node pointer is null
	this->sceneNode = 0;
	
	// set up default object values
	this->health = GAME_OBJ_MAXHEALTH;
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
